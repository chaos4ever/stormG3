/* $chaos: process.h,v 1.12 2002/10/23 21:06:58 per Exp $ */
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
 * @brief               A list of the processes in the system.
 */
extern process_t        *process_list;

/**
 * @brief               Set up the process support. 
 */
extern void process_init (void);

/**
 * @brief               Find the process with the given ID. 
 * @return              The process_t structure for this process, or NULL
 *                      if it can't be found.
 */
extern process_t *process_find (process_id_t process_id);

#endif /* !__STORM_IA32_PROCESS_H__ */
