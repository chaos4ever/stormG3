/* $chaos: memory_physical.h,v 1.9 2002/10/06 09:13:23 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file memory_physical.h
 * @brief Physical memory allocation prototypes.
 */

#ifndef __STORM_IA32_MEMORY_PHYSICAL_H__
#define __STORM_IA32_MEMORY_PHYSICAL_H__

#include <storm/types.h>
#include <storm/ia32/process.h>

/* Structures. */
/** @brief A SLAB block is used for keeping a list of all free pages. */
typedef struct 
{
    /** Unique cookie, to make sure the data structure is of the right
       type. */
    uint32_t magic_cookie;

    /** Pointer to next free SLAB. */
    struct memory_physical_slab_t *next;
} memory_physical_slab_t;

/** @brief A structure used for keeping information about which pages
    a process has allocated.

    This structure is used for holding information about the pages
    allocated for a given process. This is very useful for GC:ing the
    process when it exits. */
typedef struct
{
    /** Unique cookie, to make sure the data structure is of the right
        type. */
    uint32_t magic_cookie;

    /** The process owning this page. */
    process_id_t process_id;
  
    /** The physical address of this page. */
    void *page_address;

    /** Pointer to the previous page in this list. */
    struct memory_physical_process_page_t *previous;

    /** Pointer to the next page in this list. */
    struct memory_physical_process_page_t *next;
} memory_physical_process_page_t;

/* Variables. */
/** @brief The number of physical pages in the system. */
extern page_number_t physical_pages;

/** @brief The number of free pages. */
extern unsigned int free_pages;

/* Functions. */
/** @brief Initialize physical memory allocation. */
extern void memory_physical_init (void);

/** @brief Allocate a number of pages. */
return_t memory_physical_allocate (void **pointer, unsigned int pages);

/** @brief Allocate a page for a process. */
return_t memory_physical_allocate_for_process (void **pointer, 
                                               process_id_t process_id);

/** @brief Deallocate a page.

    Yes, only one page. If you allocated multiple
    pages, you need to call this function for each page. I will not
    keep track of the number of pages you have allocated for you, you
    will need to do it yourself. */
return_t memory_physical_deallocate (void *pointer);

/** @brief Deallocate a page for a process. */
return_t memory_physical_deallocate_for_process (void *pointer);

/** @brief Free all pages that belongs to the given process. */
return_t memory_physical_free_process (process_id_t process_id);

#endif /* !__STORM_IA32_MEMORY_PHYSICAL_H__ */
