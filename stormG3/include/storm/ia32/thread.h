/* $chaos: thread.h,v 1.3 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                thread.h
 * @brief               Thread support. 
 */

#ifndef __STORM_IA32_THREAD_H__
#define __STORM_IA32_THREAD_H__

#include <storm/ia32/tss.h>

/**
 * @brief               The thread ID of the kernel thread. (idle 
 *                      thread) 
 */
#define THREAD_ID_KERNEL                0

/**
 * @brief               Type definitions. 
 */
typedef unsigned int thread_id_t;

/**
 * @brief               A thread.
 */
typedef struct
{
    /**
     * @brief           The thread ID.
     */
    thread_id_t thread_id;

    /**
     * @brief           A lock, to make sure the integrity of the data is
     *                  maintained.
     */
    spinlock_t lock;

    /**
     * @brief           The TSS for this thread.
     */
    tss_t *tss;

    /**
     * @brief           The previous thread for this process.
     */
    struct thread_t *previous;

    /**
     * @brief           The next thread for this process.
     */
    struct thread_t *next;
} thread_t;

#endif /* !__STORM_IA32_THREAD_H__ */
