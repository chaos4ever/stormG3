/* $chaos: process.h,v 1.4 2002/10/09 09:20:00 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file process.h
 * @brief Process support. 
 */

#ifndef __STORM_IA32_PROCESS_H__
#define __STORM_IA32_PROCESS_H__

#include <storm/ia32/defines.h>
#include <storm/ia32/memory_virtual.h>
#include <storm/ia32/types.h>

/**
 * @brief The process ID of the kernel process (idle thread). 
 */
#define PROCESS_ID_KERNEL               0

/**
 * @brief The length of a process name.
 */
#define PROCESS_NAME_LENGTH             32

/**
 * @brief A unique process ID.
 */
typedef unsigned int process_id_t;

/**
 * @brief A structure with information about process.
 */
typedef struct
{
    /**
     * @brief The process ID.
     */
    process_id_t id;

    /**
     * @brief The name of the process.
     */
    char name[PROCESS_NAME_LENGTH];

    /**
     * @brief Is the process active? (as opposed to suspended for some
     * reason)
     */
    bool active;

    /**
     * @brief Pointer to the previous process.
     */
    struct process_t *previous;

    /**
     * @brief Pointer to the next process.
     */
    struct process_t *next;
} process_t;

/**
 * @brief Pre-create a process.
 *
 * Allocate a process ID and page directory for it, so we can start
 * mapping memory and set things up.
 */
extern return_t process_precreate (process_id_t *process_id, 
                                   page_directory_t **page_directory);

/**
 * @brief Create a process that's previously been pre-created.
 *
 * This function adds the process to the system list of processes and
 * includes it in the list of tasks to run. It is run at the very end
 * of a program (ELF or otherwise) loader.
 */
extern return_t process_create (process_id_t process_id,
                                address_t entry_point);

#endif /* !__STORM_IA32_PROCESS_H__ */
