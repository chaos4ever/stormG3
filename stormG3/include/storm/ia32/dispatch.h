/* $chaos: dispatch.h,v 1.6 2002/10/15 18:03:36 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                dispatch.h
 * @brief               Dispatcher prototypes.
 */

#ifndef __STORM_IA32_DISPATCH_H__
#define __STORM_IA32_DISPATCH_H__

#include <storm/ia32/process.h>
#include <storm/ia32/thread.h>
#include <storm/ia32/tss.h>

/**
 * @brief               Data structure used by the dispatcher queue.
 *
 * We use this to make a circular queue (in other words, where the
 * last entry points back to the first) of all the tasks that are
 * currently tagged as active. (A 'task' in this context is the same
 * as a thread, but 'task' is more of a CPU concept whereas 'thread'
 * is a software comncept)
 */
typedef struct
{
    /**
     * @brief           The thread that this task represents.
     */
    thread_t *thread;

    /**
     * @brief           The timeslices to let this run each time. (0-10 are
     *                  reasonable values. 
     */
    size_t timeslices;

    /**
     * @brief           The previous task in the list.
     */
    struct dispatch_t *previous;

    /**
     * @brief           The next task in the list.
     */
    struct dispatch_t *next;
} dispatch_t;

/**
 * @brief               The current thread.
 */
extern thread_t         *current_thread;

/**
 * @brief               The current process.
 */
extern process_t        *current_process;

/**
 * @brief               The kernel TSS.
 */
extern tss_t            *kernel_tss;

/**
 * @brief               The idle task. 
 *
 * Runs when no other task is active. All it does is consume CPU
 * cycles. (It would be possible to add code here for APM sleep, GC or
 * whatever) 
 */
extern void dispatch_idle (void) NORETURN;

/**
 * @brief               Initialize the dispatcher. 
 */
extern void dispatch_init (void);

/**
 * @brief               The task switcher -- IRQ0 handler. 
 */
extern void dispatch_task_switcher (void);

/**
 * @brief               Block the given thread.
 * @param thread        The thread to block. 
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t dispatch_block (thread_t *thread);

/**
 * @brief               Unblock the given thread.
 * @param thread        The thread to unblock.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t dispatch_unblock (thread_t *thread);

/**
 * @brief               The number of ticks. 
 */
extern volatile unsigned int ticks;

#endif /* !__STORM_IA32_DISPATCH_H__ */
