/* $chaos: memory_physical.c,v 1.20 2002/10/04 19:01:21 per Exp $ */
/* Abstract: Physical memory allocation. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/return_value.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/multiboot.h>
#include <storm/ia32/types.h>

/* To make all operations O(1). */
unsigned int free_pages = 0;

/* For allocation & deallocation. */
static memory_physical_slab_t *first_free = NULL;

/* A list of pages allocated by certain processes, to be able to free
   its resources when it's killed. */
memory_physical_process_page_t *process_page = NULL;

/* Used to find the end of the kernel. */
extern int _end;

// FIXME: Replace this bitmap trash with the new system. Like this:
// static memory_physical_slab_t *first_free_4k = NULL;
// static memory_physical_slab_t *first_free_8k = NULL;
// static memory_physical_slab_t *first_free_16k = NULL;
// static memory_physical_slab_t *first_free_32k = NULL;
// static memory_physical_slab_t *first_free_64k = NULL;
// static memory_physical_slab_t *first_free_128k = NULL;
// static memory_physical_slab_t *first_free_256k = NULL;
// static memory_physical_slab_t *first_free_512k = NULL;
/* The size of physical blocks that we provide. */
// static unsigned int physical_size = 512 * KIB;

/* A bitmap of all the free pages. Bit = 1 means the page is free, bit
   = 0 means the page is allocated. (Don't worry, this is not used on
   ordinary memory allocation...)
   
   FIXME: Only use the memory needed! Right now, it is always 64 KiB,
   which is what a 2 GiB system will need. */
static uint32_t physical_page_bitmap[MAX_MEMORY / PAGE_SIZE / 32];

/* The number of physical pages in the system. */
page_number_t physical_pages;

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
    /* The memory space between 640 KiB and 1 MiB is used for ISA hardware. */
    else if (page * PAGE_SIZE >= 640 * KIB && 
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
    /* More than we support. */
    else if (page * PAGE_SIZE > MAX_MEMORY)
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

    /* Link this page into the SLAB list and mark it as free in the bitmap */
    BIT_SET (physical_page_bitmap[page / 32], page % 32);
    next = (memory_physical_slab_t *) (page * PAGE_SIZE);
    next->next = (struct memory_physical_slab_t *) first_free;
    first_free = next;
    free_pages++;
}

/* Initialize physical memory allocation. */
void memory_physical_init () 
{
    uint32_t start_end;
   
    /* Clear the page bitmap */
    memory_set_uint32 (physical_page_bitmap, 0, MAX_MEMORY / PAGE_SIZE / 32);

    /* Store the number of physical pages (used later). */
    physical_pages = (1024 + multiboot_info.memory_upper) / 4;

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

/* Allocate a page for a process. */
return_t memory_physical_allocate_for_process (void **pointer, 
                                               process_id_t process_id)
{
    /* Get the page. */
    return_t return_value = memory_physical_allocate (pointer, 1);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        /* Extra security precaution. */
        *pointer = NULL;
        return return_value;
    }

    /* Register it in our structure. */
    memory_physical_process_page_t *page;
    return_value = memory_global_allocate ((void **) &page, sizeof (memory_physical_process_page_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        /* Extra security precaution. */
        return return_value;
    }

    /* Set up the data about the page. */
    page->process_id = process_id;
    page->page_address = *pointer;

    /* Link it in. */
    if (process_page != NULL)
    {
        process_page->next = (struct memory_physical_process_page_t *) page;
    }

    page->previous = (struct memory_physical_process_page_t *) process_page;
    page->next = (struct memory_physical_process_page_t *) NULL;
    process_page = page;

    return STORM_RETURN_SUCCESS;
}

/* Allocate a number of pages. */
return_t memory_physical_allocate (void **pointer, unsigned int pages) 
{
    if (first_free == NULL) 
    {
        /* This is good, so we trap code that forgets to check the
           return value. */
        *pointer = NULL;
        return STORM_RETURN_OUT_OF_MEMORY;
    }

    if (pages != 1) 
    {
        memory_physical_slab_t *slab;
        page_number_t free_page = 0;
        unsigned int has_free = 0;

        /* The algorithm for allocating multiple pages is not very
           fast, and uses quite a lot of memory. This, however, should
           not really be a problem since linear physical pages is
           really only needed in a couple of cases.

             1) When loading kernel modules and allocating memory for
             the different sections
             
             2) When allocating DMA and busmastering buffers.

           Both of these cases are very special and occur rarely, so
           even if it takes 100, 1000 or even 10000 times longer to
           allocate two pages than to allocate one, that should not
           affect the system performance. */

        /* Now, iterate through this bitmap to see whether we have a
           contigous block of the right size. */
        for (page_number_t page_number = 0; page_number < 
                 physical_pages; page_number++)
        {
            if (BIT_GET (physical_page_bitmap[page_number / 32],
                         page_number % 32) == 1)
            {
                if (has_free == 0)
                {
                    free_page = page_number;
                }
                has_free++;

                /* Do we have an area? If so, free these pages from
                   the slab structure and pass them on! */
                if (has_free == pages)
                {
                    /* Mark these pages as allocated in the bitmap */
                    for (unsigned int index = free_page; index < (free_page + pages); index++)
                    {
                        BIT_CLEAR (physical_page_bitmap[index / 32],
                                 index % 32);
                    }

                    slab = first_free;
                    while (slab != NULL)
                    {
                        volatile address_t next = (address_t) slab->next;
                        if (next >= (free_page * PAGE_SIZE) &&
                            next <= (free_page + pages - 1) * PAGE_SIZE)
                        {
                            /* Unlink this SLAB. */
                            volatile memory_physical_slab_t *block = (memory_physical_slab_t *) slab->next;
                            while (((address_t) block->next) >= (free_page * PAGE_SIZE) &&
                                   ((address_t) block->next) <= (free_page + pages - 1) * PAGE_SIZE)
                            {
                                block = (memory_physical_slab_t *) block->next;
                            }

                            slab->next = block->next;
                        }

                        slab = (memory_physical_slab_t *) slab->next;
                    }

                    free_pages -= pages;
                    *pointer = (void *) (free_page * PAGE_SIZE);
                    return STORM_RETURN_SUCCESS;
                }
            }
            else
            {
                has_free = 0;
            }
        }

        return STORM_RETURN_NOT_IMPLEMENTED;
    }
    else
    {
        uint32_t page = ((address_t) first_free) / PAGE_SIZE;
        *pointer = first_free;
        free_pages--;
        first_free = (memory_physical_slab_t *) first_free->next;
        BIT_CLEAR (physical_page_bitmap[page / 32], page % 32);
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
    uint32_t page = ((address_t) pointer) / PAGE_SIZE;
    first_free = pointer;
    first_free->next = next;
    free_pages++;
    BIT_SET (physical_page_bitmap[page / 32], page % 32);
    return STORM_RETURN_SUCCESS;
}

/* Deallocate a page for a process. */
return_t memory_physical_deallocate_for_process (void *pointer UNUSED)
{
    // FIXME: Implement this.
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Free all pages that belongs to the given process. */
return_t memory_physical_free_process (process_id_t process_id UNUSED)
{
    // FIXME: Implement this. Very simple, just 1) iterate 2)
    // deallocate 3) unlink
    return STORM_RETURN_NOT_IMPLEMENTED;
}
