/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Global memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/return_value.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/memory_physical.h>

/* Global memory slabs. */
static memory_global_slab_t *global_8byte = NULL;
static memory_global_slab_t *global_16byte = NULL;
static memory_global_slab_t *global_32byte = NULL;
static memory_global_slab_t *global_64byte = NULL;
static memory_global_slab_t *global_128byte = NULL;
static memory_global_slab_t *global_256byte = NULL;
static memory_global_slab_t *global_512byte = NULL;
static memory_global_slab_t *global_1024byte = NULL;
static memory_global_slab_t *global_2048byte = NULL;

/* Initialize global memory allocation. */
void memory_global_init ()
{
}

/* Allocate global memory. */
return_t memory_global_allocate (void **pointer, unsigned int size)
{
    memory_global_slab_t **global_slab = NULL;
    memory_global_slab_t *our_slab;
    memory_global_page_t *our_page;

    if (size <= 8) 
    {
        global_slab = &global_8byte;
        size = 8;
    }
    else if (size <= 16) 
    {
        global_slab = &global_16byte;
        size = 16;
    }
    else if (size <= 32)
    {
        global_slab = &global_32byte;
        size = 32;
    }
    else if (size <= 64)
    {
        global_slab = &global_64byte;
        size = 64;
    }
    else if (size <= 128)
    {
        global_slab = &global_128byte;
        size = 128;
    }
    else if (size <= 256)
    {
        global_slab = &global_256byte;
        size = 256;
    }
    else if (size <= 512)
    {
        global_slab = &global_512byte;
        size = 512;
    }
    else if (size <= 1024)
    {
        global_slab = &global_1024byte;
        size = 1024;
    }
    else if (size <= 2048)
    {
        global_slab = &global_2048byte;
        size = 2048;
    }
    else if (size <= 4096)
    {
        return memory_physical_allocate (pointer, 1);
    }
    else 
    {
        /* We don't support allocating bigger blocks than a page,
           since that it not O(1) in the physical memory allocator. */
        *pointer = NULL;
        return STORM_RETURN_NOT_IMPLEMENTED;
    }

    /* The slab structure we are accessing is now in
       global_slab. Start out by checking whether we need to allocate
       a page and SLABify it. */
    if (*global_slab == NULL)
    {
        void *new_page;
        unsigned int counter;
        memory_global_page_t *page;

        return_t return_value = memory_physical_allocate (&new_page, 1);
        if (return_value != STORM_RETURN_SUCCESS) 
        {
            return return_value;
        }

        /* We have a page. Lets set up the SLAB header. */
        page = (memory_global_page_t *) new_page;
        page->magic_cookie = GLOBAL_PAGE_COOKIE;
        page->used_blocks = 0;

        /* Handle the first one specially to avoid an if statement in
           the loop. */
        *global_slab = &page->slab[0];
        (*global_slab)->magic_cookie = GLOBAL_SLAB_COOKIE;
        (*global_slab)->next = NULL;

        /* Put it into our slab list. */
        for (counter = 1; 
             counter < (PAGE_SIZE - sizeof (memory_global_page_t)) / size;
             counter++)
        {
            memory_global_slab_t *slab;
            slab = (memory_global_slab_t *) (((uint32_t) &page->slab[0]) + counter * size);
            slab->next = (struct memory_global_slab_t *) *global_slab;
            *global_slab = slab;
            (*global_slab)->magic_cookie = GLOBAL_SLAB_COOKIE;
        }
    }

    /* Okay, we now know that *global_slab contains a slab structure
       that we can allocate. Just make sure that it is clean. */
    if ((*global_slab)->magic_cookie != GLOBAL_SLAB_COOKIE)
    {
        return STORM_RETURN_INTERNAL_DATA_ERROR;
    }

    // FIXME: Define a macro for this.
    our_page = (memory_global_page_t *) (((uint32_t) *global_slab) & 0xFFFFF000);
    if (our_page->magic_cookie != GLOBAL_PAGE_COOKIE)
    {
        return STORM_RETURN_INTERNAL_DATA_ERROR;
    }

    our_page->used_blocks++;

    our_slab = *global_slab;
    *global_slab = (memory_global_slab_t *) our_slab->next;
    *pointer = our_slab;
    return STORM_RETURN_SUCCESS;
}

/* Deallocate global memory. */
return_t memory_global_deallocate (void *pointer)
{
    /* Is this a 4096 block? */
    if ((uint32_t) pointer % PAGE_SIZE == 0)
    {
        return memory_physical_deallocate (pointer);
    }

    // FIXME: Implement this. It is a piece of cake.
    return STORM_RETURN_NOT_IMPLEMENTED;
}
