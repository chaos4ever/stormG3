/* $chaos: process.c,v 1.1 2002/10/10 21:39:15 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */
/* Abstract: Process support. */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/ia32/gdb.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/process.h>
#include <storm/ia32/spinlock.h>
#include <storm/ia32/string.h>
#include <storm/return_value.h>

/* The lowest free process ID. */
static process_id_t free_process_id = 1;

/* A list of processes. */
static process_t *process_list = NULL;

/* A spinlock for the process list. */
static spinlock_t process_list_lock = SPIN_UNLOCKED;

/* Find the process with the given ID. */
static process_t *process_find (process_id_t process_id)
{
    spin_lock (&process_list_lock);
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
                            page_directory_t **page_directory)
{
    /* Allocate a page directory. */
    return_t return_value = memory_global_allocate ((void **) page_directory, PAGE_SIZE);

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

    /* Create a TSS for this process. */
    return_value = memory_global_allocate ((void **) &thread->tss, sizeof (tss_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        memory_global_deallocate (thread);
        spin_unlock (&process->lock);
        return return_value;
    }

    /* Set it up. */
    thread->tss->eip = entry_point;
    thread->tss->cr3 = process->first_page_directory;
    thread->tss->cs = PROCESS_CODE_SELECTOR;
    thread->tss->ds =
        thread->tss->es =
        thread->tss->fs =
        thread->tss->gs = 
        thread->tss->ss = PROCESS_DATA_SELECTOR;
    thread->tss->eflags = TSS_NEW_EFLAGS;
    thread->tss->esp = 0;

    /* We don't allow I/O from userland. */
    thread->tss->iomap_base = sizeof (tss_t);

    /* You don't wanna have these in the wrong order. :-) */
    process->active = TRUE;
    spin_unlock (&process->lock);

    /* Add to list of active tasks for the dispatcher. */
    // FIXME: Do this.
    return STORM_RETURN_SUCCESS;
}
