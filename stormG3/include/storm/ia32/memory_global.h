/* $chaos: memory_global.h,v 1.4 2002/08/11 18:41:31 per Exp $ */
/* Abstract: Global memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_MEMORY_GLOBAL_H__
#define __STORM_IA32_MEMORY_GLOBAL_H__

#include <storm/types.h>
#ifdef STORM
#include <storm/magic_cookies.h>

/* The global slab system. Awfully simple, isn't it? */
typedef struct 
{
    /* Unique cookie, to make sure the data structure is of the right
       type. */
    uint32_t magic_cookie;

    /* Pointer to the next free slab. */
    struct memory_global_slab_t *next;
} memory_global_slab_t;

typedef struct 
{
    uint32_t magic_cookie;

    /* How many used blocks do we have in this page. If this gets down
       to zero, free the page. */
    unsigned int used_blocks;

    /* The address of our SLAB header _pointer_, used for deallocation. */
    memory_global_slab_t **slab_header;
    
    /* Here comes the slabs. Don't use this as an indexed array -- it
       won't work with slabs bigger than 8 bytes. */
    memory_global_slab_t slab[0];
} memory_global_page_t;

/* Prototypes. */
/* Initialize global memory allocation. */
extern void memory_global_init (void);

#endif /* STORM */

/* Allocate global memory. */
return_t memory_global_allocate (void **pointer, unsigned int size);

/* Deallocate global memory. */
return_t memory_global_deallocate (void *pointer);

#endif /* !__STORM_IA32_MEMORY_GLOBAL_H__ */
