/* $chaos: types.h,v 1.8 2002/10/23 07:22:57 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                ia32/types.h
 * @brief               IA32-specific types. 
 */

#ifndef __STORM_IA32_TYPES_H__
#define __STORM_IA32_TYPES_H__

#include <storm/types.h>

/**
 * @brief               A user ID.
 */
typedef                 uint32_t user_id_t;

/**
 * @brief               A group ID.
 */
typedef                 uint32_t group_id_t;

/* Things not available to userspace. */
#if (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__)

/**
 * @brief               A linear/physical address. 
 */
typedef                 uint32_t address_t;

/**
 * @brief               A page number. 
 */
typedef                 uint32_t page_number_t;

/**
 * @brief               A spin lock.
 */
typedef unsigned int spinlock_t;

/**
 * @brief               A TSS (Task State Segment).
 *
 * See the Intel Architecture Software Developer's Manual Volume 3:
 * System Programming Guide for more information about what TSS:s are
 * used for.
 */
typedef struct
{
    /**
     * @brief           CPU data. 
     */
    uint16_t            previous_task_link;
    uint16_t            u0;
    
    /**
     * @brief           Stack pointer for PL0 code (system calls). 
     */
    uint32_t            esp0;              

    /**
     * @brief           Stack segment for PL0 code (system calls).
     */
    uint16_t            ss0;

    uint16_t            u1;
    
    /**
     * @brief           Stack pointer for PL1 code (unused).
     */
    uint32_t            esp1;

    /**
     * @brief           Stack segment for PL1 code (unused).
     */
    uint16_t            ss1;
    uint16_t            u2;

    /**
     * @brief           Stack pointer for PL2 code (unused).
     */
    uint32_t            esp2;

    /**
     * @brief           Stack segment for PL2 code (unused).
     */
    uint16_t            ss2;
    uint16_t            u3;

    /**
     * @brief           CR3 (page directory) location.
     */
    uint32_t            cr3;
    
    /**
     * @brief           Instruction pointer.
     */
    uint32_t            eip;

    /**
     * @brief           Processor flags.
     */
    uint32_t            eflags;

    /**
     * @brief           General purpose register #1.
     */
    uint32_t            eax;

    /**
     * @brief           General purpose register #2.
     */
    uint32_t            ecx;

    /**
     * @brief           General purpose register #3.
     */
    uint32_t            edx;

    /**
     * @brief           General purpose register #4.
     */
    uint32_t            ebx;

    /**
     * @brief           Stack pointer. 
     */
    uint32_t            esp;

    /**
     * @brief           Base pointer.
     */
    uint32_t            ebp;

    /**
     * @brief           Source index (for MOVS)
     */
    uint32_t            esi;

    /**
     * @brief           Destination index (for MOVS)
     */
    uint32_t            edi;

    /**
     * @brief           ES segment selector.
     */
    uint16_t            es;
    uint16_t            u4;

    /**
     * @brief           CS segment selector.
     */
    uint16_t            cs;
    uint16_t            u5;

    /**
     * @brief           SS segment selector.
     */
    uint16_t            ss;
    uint16_t            u6;

    /**
     * @brief           DS segment selector.
     */
    uint16_t            ds;
    uint16_t            u7;

    /**
     * @brief           FS segment selector.
     */
    uint16_t            fs;
    uint16_t            u8;

    /**
     * @brief           GS segment selector.
     */
    uint16_t            gs;
    uint16_t            u9;
    
    /**
     * @brief           The selector in the GDT that refers to this
     *                  process LDT (Local Descriptor Table).
     *
     * We do not use this in stormG3.
     */
    uint16_t            ldt_selector;
    uint16_t            u10;
    uint16_t            t: 1;
    uint16_t            u11: 15;

    /**
     * @brief           Base address of I/O map, relative to the TSS 
     *                  location. 
     */
    uint16_t            iomap_base;
} tss_t PACKED;

/**
 * @brief               A capability.
 *
 * We could eventually move this to a more advanced data structure
 * where the capability_list is rather a list of the capability
 * classes, and the capability classes hold a list of all the
 * capabilities in this class.
 */
typedef struct
{
    /**
     * @brief           The capability ID.
     */
    char                class[CAPABILITY_CLASS_LENGTH];

    /**
     * @brief           The capability name (must be unique).
     */
    char                name[CAPABILITY_CLASS_LENGTH];

    /**
     * @brief           Pointer to the previous capability.
     */
    struct capability_t *previous;

    /**
     * @brief           Pointer to the next capability.
     */
    struct capability_t *next;
} capability_t;

/**
 * @brief               A thread.
 */
typedef struct
{
    /**
     * @brief           The thread ID.
     */
    thread_id_t         id;

    /**
     * @brief           The name of the thread.
     */
    char                name[THREAD_NAME_LENGTH];

    /**
     * @brief           The parent process to which this thread belongs.
     */
    struct process_t    *parent;

    /**
     * @brief           A lock, to make sure the integrity of the data is
     *                  maintained.
     */
    spinlock_t          lock;

    /**
     * @brief           The TSS for this thread.
     */
    tss_t               *tss;

    /**
     * @brief           The previous thread for this process.
     */
    struct thread_t     *previous;

    /**
     * @brief           The next thread for this process.
     */
    struct thread_t     *next;
} thread_t;

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

#endif /* (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__) */

#endif /* !__STORM_IA32_TYPES_H__ */
