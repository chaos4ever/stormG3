/* $chaos: dispatch.c,v 1.7 2002/10/17 21:28:58 per Exp $ */
/* Abstract: Dispatcher. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/return_value.h>
#include <storm/ia32/cpu.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/descriptor.h>
#include <storm/ia32/dispatch.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/irq.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/port.h>
#include <storm/ia32/spinlock.h>

/* Exported variables. */
/* The number of ticks since IRQ0 was first enabled. */
volatile unsigned int dispatch_ticks = 0;

/* The current thread. */
thread_t *dispatch_current_thread = NULL;

/* The current process. */
process_t *dispatch_current_process = NULL;

/* The kernel TSS. */
tss_t *dispatch_kernel_tss;

/* The current TSS. */
tss_t *dispatch_current_tss;

/* Internal variables. */
/* The current entry in the dispatch list. Used for doing the dispatching. */
static dispatch_t *dispatch_current = NULL;

/* A lock is good for avoiding concurrency problems. */
static spinlock_t dispatch_lock = SPIN_UNLOCKED;

/* A flag selecting whether we should use TSS selector 1 or 2 (0 = 1,
   1 = 2). */
static int task_flag = 0;

/* Used for doing the ljmp (I didn't get it to work with direct
   operands). */
static uint32_t jump_data[2] = { 0, 0 };

/* Block the given thread. */
return_t dispatch_block (thread_t *thread UNUSED)
{
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Unblock the given thread. (This function is O(1)) */
return_t dispatch_unblock (thread_t *thread)
{
    dispatch_t *dispatch;
    return_t return_value = memory_global_allocate ((void **) &dispatch,
                                                    sizeof (dispatch_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Set up this queue entry. */
    dispatch->thread = thread;
    // FIMXE: Support different priorities.
    dispatch->timeslices = 1;

    /* Add it to the list. This WILL NOT WORK if the list is empty --
       so please NEVER block the idle task, okay? :-) */
    spin_lock (&dispatch_lock);
    dispatch->previous = dispatch_current->previous;
    dispatch->next = (struct dispatch_t *) dispatch_current;

    /* We have to do it a slight bit different if we only have one
       running task. */
    if (dispatch_current == (dispatch_t *) dispatch_current->previous)
    {
        dispatch_current->next = (struct dispatch_t *) dispatch;
        dispatch_current->previous = (struct dispatch_t *) dispatch;
    }
    else
    {
        dispatch_t *previous = (dispatch_t *) dispatch->previous;

        previous->next = (struct dispatch_t *) dispatch;
        dispatch_current->previous = (struct dispatch_t *) dispatch;
    }

    dispatch_current->previous = (struct dispatch_t *) dispatch;
    spin_unlock (&dispatch_lock);

    return STORM_RETURN_SUCCESS;
}

/* The idle task. Runs when no other task is active. All it does is
   consume CPU cycles. (It would be possible to add code here for APM
   sleep, GC or whatever) */
void dispatch_idle (void)
{
    while (TRUE)
    {
        asm ("hlt");
    }
}

/* Initialize the dispatcher. */
void dispatch_init (void)
{
    /* Fill in some important fields in this TSS. */
    dispatch_kernel_tss->cr3 = cpu_get_cr3 ();

    /* Set up the TSS descriptor, so the CPU will know where to store
       the registers etc. */
    gdt_setup_tss_descriptor (GDT_ENTRY (TSS1_SELECTOR), dispatch_kernel_tss, 0,
                              sizeof (tss_t));

    /* Set the TR (Task Register). */
    cpu_set_tr (TSS1_SELECTOR);

    /* Make it the current so that the dispatcher know that the the
       idle thread is running. */
    dispatch_current_tss = dispatch_kernel_tss;

    /* Create the list of tasks. */
    dispatch_t *dispatch;
    return_t return_value = memory_global_allocate ((void **) &dispatch, 
                                           sizeof (dispatch_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        DEBUG_HALT ("Failed to allocate memory for dispatch_t.");
    }

    /* Set up this structure. */
    dispatch->thread = process_list->thread_list;       /* The kernel thread. */
    dispatch->timeslices = 1;
    dispatch->next = dispatch->previous = (struct dispatch_t *) dispatch;

    /* Set the current and last task to this task. */
    dispatch_current = dispatch;
}

/* The task switcher -- IRQ0 handler (called from irq_handlers.S that
   does the register preservation. */
void dispatch_task_switcher (void)
{
    dispatch_ticks++;
    asm ("movl 0xB8000, %eax\n"
         "xorl $0x10001000, %eax\n"
         "movl %eax, 0xB8000\n");

    spin_lock_interrupt (&dispatch_lock);

    /* Go go the next task. */
    dispatch_current = (dispatch_t *) dispatch_current->next;

    spin_unlock (&dispatch_lock);

    /* Okay, if it's a new one, we might as well dispatch it. */
    if (dispatch_current->thread->tss != dispatch_current_tss)
    {
        /* Toggle it. */
        task_flag ^= 1;

        /* Set it. */
        dispatch_current_tss = dispatch_current->thread->tss;

        switch (task_flag)
        {
            case 0:
            {
                gdt_setup_tss_descriptor (GDT_ENTRY (TSS1_SELECTOR),
                                          dispatch_current_tss, 3,
                                          sizeof (tss_t));
                jump_data[1] = TSS1_SELECTOR;
                break;
            }
            case 1:
            {
                gdt_setup_tss_descriptor (GDT_ENTRY (TSS2_SELECTOR),
                                          dispatch_current_tss, 3,
                                          sizeof (tss_t) - 1);
                jump_data[1] = TSS2_SELECTOR;
                break;
            }
        }

        /* Set up the "current" pointers to be right. */
        dispatch_current_thread = dispatch_current->thread;
        dispatch_current_process = (process_t *) dispatch_current->thread->parent;

        /* Do the task switch. But first ACK the interrupt so we can
           get more interrupts on this interrupt controller. */
        port_uint8_out (INTERRUPT_CONTROLLER_MASTER, 0x20);
        asm volatile ("ljmp *jump_data");

        return;
    }
    /* It's the same task, so no need to dispatch it. We just return
       silently. */
    else
    {
        return;
    }
}


