/* $chaos: memory_global.h,v 1.6 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file memory_global.h
 * @brief Global memory allocation. 
 */

#ifndef __STORM_IA32_MEMORY_GLOBAL_H__
#define __STORM_IA32_MEMORY_GLOBAL_H__

#include <storm/types.h>
#ifdef STORM
#include <storm/magic_cookies.h>

/**
 * @brief The global slab system. Awfully simple, isn't it? 
 */
typedef struct 
{
    /** 
     * @brief Unique cookie, to make sure the data structure is of the
     * right type. 
     */
    uint32_t magic_cookie;

    /**
     * @brief Pointer to the next free slab.
     *
     * We do not store any data about used blocks. This is one of the
     * points with SLAB -- it uses absolutely no memory whatsoever,
     * other than the unallocated memory, which makes it incredibly
     * efficient.
     */
    struct memory_global_slab_t *next;
} memory_global_slab_t;

/**
 * @brief A page that has been allocated for the global SLAB system.
 */
typedef struct 
{
    /**
     * @brief A unique magic cookie.
     */
    uint32_t magic_cookie;

    /**
     * @brief How many used blocks do we have in this page.
     * 
     * If this gets down to zero, free the page. 
     */
    unsigned int used_blocks;

    /**
     * @brief The address of our SLAB header _pointer_.

     * Used for deallocation. 
     */
    memory_global_slab_t **slab_header;
    
    /**
     * @brief Here comes the slabs.
     *
     * Don't use this as an indexed array -- it won't work with slabs
     * bigger than 8 bytes. 
     */
    memory_global_slab_t slab[0];
} memory_global_page_t;

/**
 * @brief Initialize global memory allocation. 
 */
extern void memory_global_init (void);

#endif /* STORM */

/**
 * @brief Allocate global memory. 
 */
return_t memory_global_allocate (void **pointer, unsigned int size);

/**
 * @brief Deallocate global memory. 
 */
return_t memory_global_deallocate (void *pointer);

#endif /* !__STORM_IA32_MEMORY_GLOBAL_H__ */
