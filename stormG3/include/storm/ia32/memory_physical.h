/* $chaos: memory_physical.h,v 1.8 2002/10/04 19:01:20 per Exp $ */
/* Abstract: Physical memory allocation prototypes. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_MEMORY_PHYSICAL_H__
#define __STORM_IA32_MEMORY_PHYSICAL_H__

#include <storm/types.h>
#include <storm/ia32/process.h>

/* Structures. */
/* The physical slab system. Awfully simple, isn't it? */
typedef struct 
{
    /* Unique cookie, to make sure the data structure is of the right
       type. */
    uint32_t magic_cookie;

    /* Pointer to next free SLAB. */
    struct memory_physical_slab_t *next;
} memory_physical_slab_t;

/* This structure is used for holding information about the pages
   allocated for a given process. This is very useful for GC:ing the
   process when it exits. */
typedef struct
{
    /* Unique cookie, to make sure the data structure is of the right
       type. */
    uint32_t magic_cookie;

    /* The process owning this page. */
    process_id_t process_id;
  
    /* The physical address of this page. */
    void *page_address;

    /* Pointer to the previous and next page in this list. */
    struct memory_physical_process_page_t *previous;
    struct memory_physical_process_page_t *next;
} memory_physical_process_page_t;

/* Functions. */
/* The number of physical pages in the system. */
extern page_number_t physical_pages;

/* The number of free pages. */
extern unsigned int free_pages;

/* Initialize physical memory allocation. */
extern void memory_physical_init (void);

/* Allocate a number of pages. */
return_t memory_physical_allocate (void **pointer, unsigned int pages);

/* Allocate a page for a process. */
return_t memory_physical_allocate_for_process (void **pointer, 
                                               process_id_t process_id);

/* Deallocate a page. Yes, only one page. If you allocated multiple
   pages, you need to call this function for each page. I will not
   keep track of the number of pages you have allocated for you, you
   will need to do it yourself. */
return_t memory_physical_deallocate (void *pointer);

/* Deallocate a page for a process. */
return_t memory_physical_deallocate_for_process (void *pointer);

/* Free all pages that belongs to the given process. */
return_t memory_physical_free_process (process_id_t process_id);

#endif /* !__STORM_IA32_MEMORY_PHYSICAL_H__ */
