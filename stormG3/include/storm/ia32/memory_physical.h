/* $chaos: memory_physical.h,v 1.13 2002/10/22 19:42:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                memory_physical.h
 * @brief               Physical memory allocation prototypes.
 */

#ifndef __STORM_IA32_MEMORY_PHYSICAL_H__
#define __STORM_IA32_MEMORY_PHYSICAL_H__

#include <storm/types.h>
#include <storm/ia32/process.h>

/** 
 * @brief               A SLAB block is used for keeping a list of all
 *                      free pages. 
 */
typedef struct 
{
    /**
     * @brief           Unique cookie, to make sure the data structure 
     *                  is of the right type. */
    uint32_t magic_cookie;

    /**
     * @brief           Pointer to next free SLAB. 
     */
    struct memory_physical_slab_t *next;
} memory_physical_slab_t;

/**
 * @brief               A structure used for keeping information about
 *                      which pages a process has allocated.
 *
 * This structure is used for holding information about the pages
 * allocated for a given process. This is very useful for GC:ing the
 * process when it exits. 
 */
typedef struct
{
    /**
     * @brief           Unique cookie, to make sure the data structure is of
     *                  the right type. 
     */
    uint32_t            magic_cookie;

    /**
     * @brief           The process owning this page/these pages.
     */
    process_id_t        process_id;
  
    /**
     * @brief           The physical address of this page/these pages. 
     */
    void                *page_address;

    /**
     * @brief           The number of pages this node contains.
     */
    size_t              pages;

    /**
     * @brief           Pointer to the previous page in this list. 
     */
    struct memory_physical_process_page_t 
                        *previous;

    /**
     * @brief           Pointer to the next page in this list. 
     */
    struct memory_physical_process_page_t
                        *next;
} memory_physical_process_page_t;

/**
 * @brief               The total number of physical pages in the system. 
 */
extern page_number_t physical_pages;

/**
 * @brief               The number of free pages. 
 */
extern unsigned int free_pages;

/**
 * @brief               Initialize physical memory allocation. 
 */
void memory_physical_init (void);

/**
 * @brief               Free pages that was used during startup. 
 */
void memory_physical_done (void);

/** 
 * @brief               Free all pages that belongs to the given process. 
 * @param process_id    The process ID of the process.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
return_t memory_physical_free_process (process_id_t process_id);

#endif /* !__STORM_IA32_MEMORY_PHYSICAL_H__ */
