/* $chaos: process.c,v 1.8 2002/10/23 21:20:29 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */
/* Abstract: Process support. */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/ia32/debug.h>
#include <storm/ia32/dispatch.h>
#include <storm/ia32/gdb.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/process.h>
#include <storm/ia32/spinlock.h>
#include <storm/ia32/string.h>
#include <storm/return_value.h>

/* A list of processes. */
process_t *process_list = NULL;

/* The lowest free process ID. */
static process_id_t free_process_id = 1;

/* A spinlock for the process list. */
static spinlock_t process_list_lock = SPIN_UNLOCKED;

/* Set up the process support. */
void process_init (void)
{
    /* Allocate memory for kernel process. */
    process_t *process;
    return_t return_value = memory_global_allocate ((void **) &process, sizeof (process_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_HALT ("Failed to allocate memory for kernel process");
    }

    /* Allocate memory for kernel thread. */
    thread_t *thread;
    return_value = memory_global_allocate ((void **) &thread, sizeof (thread_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_HALT ("Failed to allocate memory for kernel thread");
    }

    /* Allocate memory for kernel TSS. */
    return_value = memory_global_allocate ((void **) &kernel_tss, sizeof (tss_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_HALT ("Failed to allocate memory for kernel TSS.");
    }

    // FIXME: Have a function for allocating thread IDs.
    thread->id = 0;
    string_copy_max (thread->name, "Idle thread", THREAD_NAME_LENGTH);
    thread->parent = (struct process_t *) process;
    thread->lock = SPIN_UNLOCKED;
    thread->tss = kernel_tss;
    thread->previous = thread->next = NULL;

    memory_set_uint8 ((void *) process, 0, sizeof (process_t));
    process->id = 0;
    string_copy_max (process->name, "Kernel process", PROCESS_NAME_LENGTH);
    process->active = TRUE;
    process->thread_list = thread;
    process->lock = SPIN_UNLOCKED;
    process_list = process;
    
    /* The kernel process gets the super_user privilege. That way, the
       first process (usually the boot program) will inherit these
       privileges so that it can do everything that it needs. */
    capability_add (PROCESS_ID_NONE, process, "kernel", "super_user");
}

/* Find the process with the given ID. */
process_t *process_find (process_id_t process_id)
{
    spin_lock_interrupt (&process_list_lock);
    process_t *process = process_list;

    while (process != NULL)
    {
        if (process->id == process_id)
        {
            spin_unlock (&process_list_lock);
            return process;
        }

        process = (process_t *) process_list->next;
    }

    spin_unlock (&process_list_lock);
    return NULL;
}

/* Find a free process ID. */
static process_id_t process_find_free_id (void)
{
    process_id_t process_id;

    /* This MAY lock in a very special case: if all process ID's are
       allocated, it will lock for ever if run within locked code. Be
       aware of this! */
    do 
    {
        process_id = free_process_id++;
    } while (process_id == 0 || process_find (process_id) != NULL);

    return process_id;
}

/* Process "pre-creator"; allocate a process ID and page directory. */
return_t process_precreate (process_id_t *process_id, 
                            void **page_directory)
{
    /* Allocate a page directory. */
    return_t return_value = memory_global_allocate (page_directory, PAGE_SIZE);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Allocate a process_t structure. */
    process_t *process;
    return_value = memory_global_allocate ((void **) &process, sizeof (process_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        /* Make sure we don't leak the page directory. */
        memory_global_deallocate (*page_directory);
        return return_value;
    }

    /* Clear the page directory. */
    memory_clear_page (*page_directory);

    /* Map the physical memory. We skip the first page to trap NULL
       references. */
    memory_virtual_map (*page_directory, 1, 1, 
                        physical_pages - 1, PAGE_KERNEL);

    /* Get a process ID. */
    *process_id = process_find_free_id ();

    string_copy_max (process->name, "Unnamed", PROCESS_NAME_LENGTH);
    process->id = *process_id;
    process->lock = SPIN_UNLOCKED;
    process->first_page_directory = (address_t) *page_directory;
    process->active = FALSE; /* Make sure the dispatcher won't take it
                                and try to run it. */
    process->next = NULL;

    /* Lock and update the structure. */
    spin_lock (&process_list_lock);
    process->previous = (struct process_t *) process_list;
    if (process_list == NULL)
    {
        process_list = process;
    }
    else
    {
        process_list->next = (struct process_t *) process;
    }
    spin_unlock (&process_list_lock);

    /* Over and out. */
    return STORM_RETURN_SUCCESS;
}

/* Create the process. */
return_t process_create (process_id_t process_id UNUSED,
                         address_t entry_point UNUSED)
{
    process_t *process = process_find (process_id);
    
    if (process == NULL)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    /* Lock this process. It should really not be neccessary since the
       process has not been started yet. The only reentrancy that I
       could imagine is if you would run process_create () for the
       same process_id simultaneously... but we may as well do it the
       Clean Way. It does not hurt. */
    spin_lock (&process->lock);

    /* Create a thread for this process. */
    thread_t *thread;
    return_t return_value = memory_global_allocate ((void **) &thread, sizeof (thread_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        spin_unlock (&process->lock);
        return return_value;
    }

    thread->parent = (struct process_t *) process;

    /* Create a TSS for this process. */
    return_value = memory_global_allocate ((void **) &thread->tss, sizeof (tss_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        memory_global_deallocate (thread);
        spin_unlock (&process->lock);
        return return_value;
    }

    /* Set it up properly. */
    //    debug_print ("EIP: %x\n", entry_point);
    thread->tss->eip = entry_point;
    thread->tss->cr3 = process->first_page_directory;
    thread->tss->cs = PROCESS_CODE_SELECTOR;
    thread->tss->ds =
        thread->tss->es =
        thread->tss->fs =
        thread->tss->gs = 
        thread->tss->ss = PROCESS_DATA_SELECTOR;

    thread->tss->eflags = TSS_NEW_EFLAGS;

    /* Set up PL0 stack (neccessary; the CPU switches automatically
       when going into an interrupt for example). */
    thread->tss->ss0 = KERNEL_DATA_SELECTOR;
    void *stack;
    return_value = memory_physical_allocate ((void *) &stack, 1, ((process_t *) thread->parent)->id);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_HALT ("Failed allocating privileged stack for process.");
    }
    thread->tss->esp0 = ((address_t) stack) + PAGE_SIZE;

    thread->tss->esp = 0;

    /* We don't allow I/O from userland. */
    thread->tss->iomap_base = sizeof (tss_t);

    /* You don't wanna have these in the wrong order. :-) */
    process->active = TRUE;
    spin_unlock (&process->lock);

    /* Add this thread to the list of tasks in the dispatcher. */
    dispatch_unblock (thread);

    /* Add to list of active tasks for the dispatcher. */
    // FIXME: Do this.
    return STORM_RETURN_SUCCESS;
}
