/* $chaos: memory_physical.c,v 1.8 2002/06/15 14:37:40 per Exp $ */
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

/* Add the given page to the SLAB, if it is not used by a kernel
   module, DMA buffers or something like that. */
static void check_and_add_page (unsigned int page)
{
    memory_physical_slab_t *next;

    /* We don't map the NULL page, so we can trap bad pointer
       references. */
    if (page == 0)
    {
        return;
    }
    /* The memory space between DMA_BASE and up to the 640 KiB point
       is used by DMA buffers. These can easily be freed later on, but
       they are a pain to allocate when memory fragmentation has
       started. */
    else if (page * PAGE_SIZE >= DMA_BASE && 
             page * PAGE_SIZE < 1 * MIB)
    {
        return;
    }
    /* Kernel memory. */
    else if (page * PAGE_SIZE >= KERNEL_BASE &&
             page * PAGE_SIZE <= (uint32_t) &_end)
    {
        return;
    }
    
    /* Finally, make sure this memory doesn't overlap with a kernel
       module. */
    for (unsigned int counter = 0; counter < multiboot_info.number_of_modules; 
         counter++) 
    {
        if (page * PAGE_SIZE >= multiboot_module_info[counter].start &&
            page * PAGE_SIZE <= multiboot_module_info[counter].end)
        {
            return;
        }
    }

    next = (memory_physical_slab_t *) (page * PAGE_SIZE);
    next->next = (struct memory_physical_slab_t *) first_free;
    first_free = next;
    free_pages++;
}

/* Initialize physical memory allocation. */
void memory_physical_init () 
{
    uint32_t start_end;
   
    /* If we have a Multiboot memory map, we can use it to avoid using
       any registered memory areas (used for hardware devices etc). */
    if (multiboot_info.has_memory_map == 1)
    {
        for (int index = 0; index * sizeof (multiboot_memory_map_t) <
                 multiboot_info.memory_map_length; index++)
        {
            if (multiboot_memory_map[index].type == 1) /* RAM. */
            {
                uint32_t startpage = (multiboot_memory_map[index].base_address /
                                      PAGE_SIZE);
                uint32_t pages = multiboot_memory_map[index].length / PAGE_SIZE;
                for (uint32_t page = startpage; page < startpage + pages;
                     page++)
                {
                    check_and_add_page (page);
                }
            }
        }
    }
    else /* Nope, no memory map. But we still have some great help
            from our Multiboot loader. */
    {
        /* Map the low pages we have into our slab structure. We don't
           care about getting this from the memory map; we blindly
           presume there ise 640KiB lower memory. I have personally a
           machine that reports 639 KiB, but I believe it is simply
           lying. */
        for (uint32_t page = 0; page < (multiboot_info.memory_lower * KIB) / 
                 PAGE_SIZE; page++) 
        {
            check_and_add_page (page);
        }

        /* Now, take care of the high pages, starting with the page right
           after _end. */
        start_end = ((uint32_t) &_end) / PAGE_SIZE + 1;
        for (uint32_t page = start_end; 
             page < (1 * MIB + multiboot_info.memory_upper * KIB) / PAGE_SIZE;
             page++) 
        {
            check_and_add_page (page);
        }
    }   
    
    /* Scanning done, over and out. */
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
