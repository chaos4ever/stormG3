/* $chaos: xemacs-script,v 1.7 2002/06/04 22:24:43 per Exp $ */
/* Abstract: Physical memory allocation prototypes. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_MEMORY_PHYSICAL_H__
#define __STORM_IA32_MEMORY_PHYSICAL_H__

/* The physical slab system. Awfully simple, isn't it? */
typedef struct {
    struct memory_physical_slab_t *next;
} memory_physical_slab_t;

/* Initialize physical memory allocation. */
extern void memory_physical_init (void);

/* Allocate a number of pages. */
return_type memory_physical_allocate (void **pointer, unsigned int pages);

/* Deallocate a page. Yes, only one page. If you allocated multiple
   pages, you need to call this function for each page. I will not
   keep track of the number of pages you have allocated for you, you
   will need to do it yourself. */
return_type memory_physical_deallocate (void *pointer);

#endif /* !__STORM_IA32_MEMORY_PHYSICAL_H__ */