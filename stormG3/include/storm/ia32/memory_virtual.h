/* $chaos: memory_virtual.h,v 1.7 2002/10/21 20:53:29 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                        memory_virtual.h
 * @brief                       Virtual memory prototypes and data structures. 
 */

#ifndef __STORM_IA32_MEMORY_VIRTUAL_H__
#define __STORM_IA32_MEMORY_VIRTUAL_H__

/**
 * @brief               Flags used when creating new entries in the page
 *                      directory.
 *
 * We let the page table set everything, so we need to have this
 * all-privileged. 
 */
#define PAGE_DIRECTORY_FLAGS \
                        (PAGE_WRITABLE | PAGE_NON_PRIVILEGED)

/**
 * @brief               A page directory entry (PDE) when using 4MiB pages. 
 */
typedef struct
{
    uint32_t            present              : 1;
    uint32_t            flags                : 4;
    uint32_t            accessed             : 1;
    uint32_t            dirty                : 1;
    
    /**
     * @brief           Should always be one (4 MiB pages, no page 
     *                  tables). 
     */
    uint32_t            page_size            : 1;
    uint32_t            global               : 1;
    uint32_t            available            : 3;
    
    /**
     * @brief           Should always be zero.
     */
    uint32_t            zero                 : 10;

    /**
     * @brief           The physical base of this page, shifted 20 steps 
     *                  to the right.
     */
    uint32_t            page_base            : 10;
} page_directory_4mb_t;

/**
 * @brief               A page directory entry (PDE).
 */
typedef struct
{
    uint32_t            present              : 1;
    uint32_t            flags                : 4;
    uint32_t            accessed             : 1;
    uint32_t            zero                 : 1;
    
    /**
     * @brief           Should always be zero (4 KiB pages).
     */
    uint32_t            page_size            : 1;
    uint32_t            global               : 1;
    uint32_t            available            : 3;
    uint32_t            page_table_base      : 20;
} page_directory_t;

/**
 * @brief A page table entry (PTE). 
 */
typedef struct
{
    uint32_t present              : 1;
    uint32_t flags                : 4;
    uint32_t accessed             : 1;
    uint32_t dirty                : 1;
    uint32_t zero                 : 1;
    uint32_t global               : 1;
    uint32_t available            : 3;
    uint32_t page_base            : 20;
} page_table_t;

/** 
 * @brief               Initialize the virtual memory system. 
 */
extern void memory_virtual_init (void);

#endif /* !__STORM_IA32_MEMORY_VIRTUAL_H__ */
