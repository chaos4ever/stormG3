/* $chaos: memory_physical.h,v 1.7 2002/08/11 18:41:12 per Exp $ */
/* Abstract: Physical memory allocation prototypes. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_MEMORY_PHYSICAL_H__
#define __STORM_IA32_MEMORY_PHYSICAL_H__

#include <storm/types.h>

/* The physical slab system. Awfully simple, isn't it? */
typedef struct 
{
    /* Unique cookie, to make sure the data structure is of the right
       type. */
    uint32_t magic_cookie;

    /* Pointer to next free SLAB. */
    struct memory_physical_slab_t *next;
} memory_physical_slab_t;

/* The number of physical pages in the system. */
extern page_number_t physical_pages;

/* The number of free pages. */
extern unsigned int free_pages;

/* Initialize physical memory allocation. */
extern void memory_physical_init (void);

/* Allocate a number of pages. */
return_t memory_physical_allocate (void **pointer, unsigned int pages);

/* Deallocate a page. Yes, only one page. If you allocated multiple
   pages, you need to call this function for each page. I will not
   keep track of the number of pages you have allocated for you, you
   will need to do it yourself. */
return_t memory_physical_deallocate (void *pointer);

#endif /* !__STORM_IA32_MEMORY_PHYSICAL_H__ */
