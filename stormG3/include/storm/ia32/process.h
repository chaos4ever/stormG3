/* $chaos: process.h,v 1.10 2002/10/22 19:41:48 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                process.h
 * @brief               Process support. 
 */

#ifndef __STORM_IA32_PROCESS_H__
#define __STORM_IA32_PROCESS_H__

#include <storm/storm.h>
#include <storm/ia32/capability.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/memory_virtual.h>
#include <storm/ia32/spinlock.h>
#include <storm/ia32/thread.h>
#include <storm/ia32/types.h>

/**
 * @brief               The process ID of the kernel process (idle thread). 
 */
#define PROCESS_ID_KERNEL \
                        0

/**
 * @brief               A process ID indicating 'no process'.
 *
 * Used in memory_allocate() in the beginning when we allocate memory
 * that's not registered in the process-page list.
 */
#define PROCESS_ID_NONE \
                        ((process_id_t) -1)

/**
 * @brief               The length of a process name.
 */
#define PROCESS_NAME_LENGTH \
                        32

/**
 * @brief               A structure with information about process.
 */
typedef struct
{
    /**
     * @brief           The process ID.
     */
    process_id_t        id;

    /**
     * @brief           The name of the process.
     */
    char                name[PROCESS_NAME_LENGTH];

    /**
     * @brief           The owner user of this process.
     */
    user_id_t           user_id;

    /**
     * @brief           The active group ID for this process.
     */
    group_id_t          active_group_id;

    /**
     * @brief           A linked list of capbilities.
     */
    capability_t        *capability_list;

    /**
     * @brief           A lock for this structure.
     */
    spinlock_t          lock;

    /**
     * @brief           Is the process active? (as opposed to suspended 
     *                  for some reason)
     */
    bool                active;

    /**
     * @brief           The address to the first page directory in this
     *                  process; used for communication between
     *                  process_precreate and process_create.
     */
    address_t           first_page_directory;

    /**
     * @brief           A list of threads belonging to this process.
     */
    thread_t            *thread_list;

    /**
     * @brief           Pointer to the previous process.
     */
    struct process_t    *previous;

    /**
     * @brief           Pointer to the next process.
     */
    struct process_t    *next;
} process_t;

/**
 * @brief               A list of the processes in the system.
 */
extern process_t        *process_list;

/**
 * @brief               Set up the process support. 
 */
extern void process_init (void);

#endif /* !__STORM_IA32_PROCESS_H__ */
