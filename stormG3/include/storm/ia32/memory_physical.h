/* $chaos: memory_physical.h,v 1.10 2002/10/08 20:16:14 per Exp $ */
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
    uint32_t magic_cookie;

    /**
     * @brief           The process owning this page. 
     */
    process_id_t process_id;
  
    /**
     * @brief           The physical address of this page. 
     */
    void *page_address;

    /**
     * @brief           Pointer to the previous page in this list. 
     */
    struct memory_physical_process_page_t *previous;

    /**
     * @brief           Pointer to the next page in this list. 
     */
    struct memory_physical_process_page_t *next;
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
 * @brief               Allocate a number of pages. 
 * @param pointer       A double pointer to where the function will put
 *                      a pointer to the allocated memory.
 * @param pages         The number of pages to allocate. (1 is O(1),
 *                      more is much, much slower)
 * @return              STORM_RETURN_SUCCESS if successful.
 *
 * FIXME: Merge this with the next one. The kernel should be treated
 * as a process with PROCESS_ID_KERNEL. That way, it will be possible
 * (and very easy) to see exactly how much memory the kernel has
 * allocated. However... there may be a BIG problem with this; the
 * information is stored in memory_global_allocate'd memory and that
 * function gets its memory from memory_physical_allocate, so we would
 * have a loop... Think about this.
 */
return_t memory_physical_allocate (void **pointer, unsigned int pages);

/**
 * @brief               Allocate a page for a process. 
 * @param pointer       A double pointer to where the function will put
 *                      a pointer to the allocated memory.
 * @param process_id    The process ID to allocate the memory for.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
return_t memory_physical_allocate_for_process (void **pointer, 
                                               process_id_t process_id);

/**
 * @brief               Deallocate a page.
 * @param pointer       A pointer to the page.
 * @return              STORM_RETURN_SUCCESS if successful.
 *
 * Yes, only one page. If you allocated multiple
 * pages, you need to call this function for each page. I will not
 * keep track of the number of pages you have allocated for you, you
 * will need to do it yourself. 
 */
return_t memory_physical_deallocate (void *pointer);

/**
 * @brief               Deallocate a page for a process. 
 * @param pointer       A pointer to the page.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
return_t memory_physical_deallocate_for_process (void *pointer);

/** 
 * @brief               Free all pages that belongs to the given process. 
 * @param process_id    The process ID of the process.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
return_t memory_physical_free_process (process_id_t process_id);

#endif /* !__STORM_IA32_MEMORY_PHYSICAL_H__ */
