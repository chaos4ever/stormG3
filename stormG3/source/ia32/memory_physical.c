/* $chaos: memory_physical.c,v 1.7 2002/06/15 14:34:38 per Exp $ */
/* Abstract: Physical memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/return_value.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/multiboot.h>

/* To make all operations O(1). */
static unsigned int free_pages = 0;

/* For allocation & deallocation. */
static memory_physical_slab_t *first_free = NULL;

/* Used to find the end of the kernel. */
extern int _end;

/* Initialize physical memory allocation. */
void memory_physical_init () 
{
    /* Mark all pages as free, except for the ones explicitly marked
       as used by the kernel. FIXME: Use the memory map that we got
       from the Multiboot loader, it will make things work even better
       on some computers. */

    uint32_t start_end;
    uint32_t page;

    /* Map the low pages we have into our slab structure. */
    for (page = 1; page < DMA_BASE / PAGE_SIZE; page++) 
    {
        memory_physical_slab_t *next = (memory_physical_slab_t *) (page * PAGE_SIZE);
        next->next = (struct memory_physical_slab_t *) first_free;
        first_free = next;
        free_pages++;
    }

    /* Now, take care of the high pages, starting with the page right
       after _end. */
    start_end = ((uint32_t) &_end) / PAGE_SIZE + 1;
    for (page = start_end; 
         page < (1 * MIB + multiboot_info.memory_upper * KIB) / PAGE_SIZE;
         page++) 
    {
        memory_physical_slab_t *next = (memory_physical_slab_t *) (page * PAGE_SIZE);
        next->next = (struct memory_physical_slab_t *) first_free;
        first_free = next;
        free_pages++;
    }

    debug_print ("Free memory: %u pages, %u KiB, %u MiB.\n", 
                 free_pages, free_pages * 4, free_pages / 256);
}

/* Allocate a number of pages. */
return_t memory_physical_allocate (void **pointer, unsigned int pages) 
{
    if (pages != 1) 
    {
        /* FIXME: Implement, by means of reserved buffers or
           sweep-n-scan. */
        return STORM_RETURN_NOT_IMPLEMENTED;
    }

    *pointer = first_free;
    if (first_free == NULL) 
    {
        return STORM_RETURN_OUT_OF_MEMORY;
    }
    else 
    {
        first_free = (memory_physical_slab_t *) first_free->next;
    }

    return STORM_RETURN_SUCCESS;
}

/* Deallocate a page. Yes, only one page. If you allocated multiple
   pages, you need to call this function for each page. I will not
   keep track of the number of pages you have allocated for you, you
   will need to do it yourself. */
return_t memory_physical_deallocate (void *pointer) 
{
    void *next = first_free;
    first_free = pointer;
    first_free->next = next;
    return STORM_RETURN_SUCCESS;
}
