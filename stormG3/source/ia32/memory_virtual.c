/* $chaos: memory_virtual.c,v 1.11 2002/10/23 07:21:26 per Exp $ */
/* Abstract: Virtual memory routines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/return_value.h>
#include <storm/ia32/bit.h>
#include <storm/ia32/cpu.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/memory_virtual.h>
#include <storm/ia32/multiboot.h>

/* Set to TRUE if you want debug information. */
#undef DEBUG

// FIXME: Use PGE. This requires some CPU detection code in cpu.c

/* The kernel page directory. */
static page_directory_t *kernel_page_directory;

/* Create an entry in a page table. */
static void create_page_table_entry (page_table_t *page_table, 
                                     unsigned int entry, 
                                     unsigned int physical_page,
                                     unsigned int flags)
{
#if DEBUG
    debug_print ("%x %u %x %u\n", page_table, entry, physical_page, flags);
#endif

    page_table[entry].present = 1;
    page_table[entry].flags = (flags & 0xF);
    page_table[entry].accessed = 0;
    page_table[entry].zero = 0;
    page_table[entry].dirty = 0;
    page_table[entry].global = ((flags & PAGE_GLOBAL) == 1) ? 1 : 0;
    page_table[entry].available = 0;
    page_table[entry].page_base = physical_page;
}

/* Create an entry in a page directory. */
static void create_page_directory_entry (page_directory_t *page_directory,
                                         unsigned int entry,
                                         unsigned int page_table_page,
                                         unsigned int flags)
{
#if DEBUG
    debug_print ("Create PDE: %x %u %x %u\n", page_directory, entry, page_table_page, flags);
#endif    

    page_directory[entry].present = 1;
    page_directory[entry].flags = PAGE_DIRECTORY_FLAGS;
    page_directory[entry].accessed = 0;
    page_directory[entry].zero = 0;
    page_directory[entry].page_size = 0;
    page_directory[entry].global = ((flags & PAGE_GLOBAL) == 1) ? 1 : 0;
    page_directory[entry].available = 0;
    page_directory[entry].page_table_base = page_table_page;
}

#if FALSE
/* Create an entry in a page directory using 4 MB pages. */
static void create_page_directory_entry_4mb (page_directory_t *page_directory,
                                             unsigned int entry,
                                             unsigned int page_table_page,
                                             unsigned int flags)
{
    page_directory[entry].present = 1;
    page_directory[entry].flags = PAGE_DIRECTORY_FLAGS;
    page_directory[entry].accessed = 0;
    page_directory[entry].zero = 0;
    page_directory[entry].page_size = 1;
    page_directory[entry].global = ((flags & PAGE_GLOBAL) == 1) ? 1 : 0;
    page_directory[entry].available = 0;
    page_directory[entry].page_table_base = page_table_page;
}
#endif

/* Find a mapping. */
return_t memory_virtual_find (void *page_directory_void,
                              page_number_t virtual_page,
                              page_number_t *physical_page,
                              unsigned int *flags)
{
    page_directory_t *page_directory = (page_directory_t *) page_directory_void;
    unsigned int page_directory_index = virtual_page / 1024;
    unsigned int page_table_index = virtual_page % 1024;
    if (page_directory[page_directory_index].present == 0)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    page_table_t *page_table = (page_table_t *) (page_directory[page_directory_index].page_table_base * PAGE_SIZE);
    if (page_table[page_table_index].present == 0)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    *flags = page_table[page_table_index].flags;
    *physical_page = page_table[page_table_index].page_base;

    return STORM_RETURN_SUCCESS;
}

/* Map memory. */
return_t memory_virtual_map (void *page_directory_void,
                             page_number_t virtual_page,
                             page_number_t physical_page,
                             unsigned int pages, unsigned int flags) 
{
    uint32_t counter;
    page_directory_t *page_directory = (page_directory_t *) page_directory_void;

#if DEBUG
    debug_print ("Mapping memory: %x %x %x %u %u\n", page_directory,
                 virtual_page, physical_page, pages, flags);
#endif

    /* Main loop. */
    for (counter = 0; counter < pages; counter++) {
        uint32_t page_directory_index = (virtual_page + counter) / 1024;
        uint32_t page_table_index = (virtual_page + counter) % 1024;
        page_table_t *page_table;

        if (page_directory[page_directory_index].present == 0) 
        {
            /* We need to set up a page table. */
            if (memory_physical_allocate((void **) &page_table, 1, PROCESS_ID_KERNEL) != STORM_RETURN_SUCCESS)
            {
                DEBUG_HALT ("Failed to allocate a page for the page table.");
            }

            /* Make sure it is cleared out. */
            memory_clear_page (page_table);

            /* Set up the page directory entry, referring to this
               newly created page table. */
            create_page_directory_entry (page_directory, page_directory_index,
                                         ((address_t) page_table) / PAGE_SIZE, 
                                         PAGE_DIRECTORY_FLAGS);
        }
        else 
        {
            page_table = (page_table_t *) (page_directory[page_directory_index].page_table_base * PAGE_SIZE);
        }

        /* Now, we have a page table. Create an entry. */
        create_page_table_entry (page_table, page_table_index, 
                                 physical_page + counter, flags);
    }

    return STORM_RETURN_SUCCESS;
}

/* Initialize the virtual memory system. */
void memory_virtual_init ()
{
    /* Allocate a page for the kernel page directory. */
    if (memory_physical_allocate((void **) &kernel_page_directory, 1, PROCESS_ID_KERNEL) != STORM_RETURN_SUCCESS)
    {
        DEBUG_HALT ("Failed to allocate a page for the kernel page directory.");
    }

    /* Make sure it is cleared out. */
    memory_clear_page (kernel_page_directory);

    /* Map the physical memory. We skip the first page to trap NULL
       references. */
    memory_virtual_map (kernel_page_directory, 1, 1, 
                        physical_pages - 1, PAGE_KERNEL);
    
    /* Specify page directory to use for the kernel. */
    cpu_set_cr3 ((address_t) kernel_page_directory); 

    /* Enable paging (virtual memory), protection and set the extension
       type flag. */
    cpu_set_cr0 (CPU_CR0_PE | CPU_CR0_PG | CPU_CR0_ET);
}
