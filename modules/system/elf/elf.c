/* $chaos: elf.c,v 1.8 2002/10/23 07:30:50 per Exp $ */
/* Abstract: ELF module, implementing the exec service. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <exec/exec.h>
#include <memory/memory.h>

#include "elf.h"

/* Make sure this is a valid ELF for our platform. */
static return_t elf_identify (elf_header_t *elf_header)
{
    /* First of all, make sure this is an ELF image... */
    if (!(elf_header->identification[0] == 0x7F &&
          elf_header->identification[1] == 'E' && 
          elf_header->identification[2] == 'L' &&
          elf_header->identification[3] == 'F'))
    {
        debug_print ("No ELF header found.\n");
        return STORM_RETURN_MODULE_INVALID;
    }

    /* ...and a 32-bit one, little-endian, relocatable... */
    if (elf_header->class != ELF_CLASS_32BIT ||
        elf_header->endian != ELF_ENDIAN_LITTLE ||
        elf_header->type != ELF_TYPE_EXECUTABLE ||
        elf_header->version != ELF_VERSION_CURRENT ||
        elf_header->machine != ELF_MACHINE_386)
    {
        debug_print ("Invalid type of ELF detected.\n");
        return STORM_RETURN_MODULE_INVALID;
    }

    return STORM_RETURN_SUCCESS;
}

/* Load an ELF. Allocate memory for it, and copy the data from the
   different sections there. */
static return_t elf_load (elf_header_t *elf_header, 
                          process_id_t process_id,
                          void *page_directory)
{
    return_t return_value;

    /* Find the highest end address of a section. This presumes that
       the sections come right after each other, which is a reasonable
       presumption since we control ELF generation for our OS. */
    for (int index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = (elf_section_header_t *) (((uint32_t) elf_header) + elf_header->section_header_offset + (index * elf_header->section_header_entry_size));

        if (section_header->flags & ELF_SECTION_FLAG_ALLOCATE &&
            section_header->type == ELF_SECTION_TYPE_PROGRAM)
        {
            void *buffer; 
            unsigned int remaining_size = section_header->size;
            size_t file_offset = 0;
            unsigned int page_offset = 0;

            /* If the first page is not page aligned, handle it
               slightly differently. */
            if (section_header->address % PAGE_SIZE != 0)
            {
                unsigned int offset = section_header->address % PAGE_SIZE;
                size_t size = MIN(section_header->size, PAGE_SIZE - offset);
                // debug_print ("Section header size: %x\n",
                // section_header->size);

                /* If this section overlaps another section, find the
                   physical addres of the page that has already been
                   mapped at this place. */
                unsigned int flags;
                page_number_t page_number;
                return_value = memory_virtual_find (page_directory, PAGE_NUMBER (section_header->address), &page_number, &flags);

                /* Yes -- use this physical address instead. */
                // FIXME: Check that the flags are valid.
                if (return_value == STORM_RETURN_SUCCESS)
                {
                    buffer = (void *) (page_number * PAGE_SIZE);
                }
                /* The page is not mapped, so map it please. */
                else 
                {
                    /* Allocate memory for this section and map it at
                       the right place. */
                    return_value = memory_physical_allocate (&buffer, 1, process_id);
                    if (return_value != STORM_RETURN_SUCCESS)
                    {
                        debug_print ("Failed to allocate memory");
                        return return_value;
                    }
                    
                    /* Map this memory at the right place. */
                    // FIXME: Get some of the flags from the section
                    // (like writable).
                    return_value = memory_virtual_map
                        (page_directory, 
                         PAGE_NUMBER (section_header->address),
                         PAGE_NUMBER (buffer), 1, PAGE_USER);
                    if (return_value != STORM_RETURN_SUCCESS)
                    {
                        debug_print ("Failed to map memory");
                        return return_value;
                    }
                }                    
                
#if DEBUG
                debug_print ("Copying to %x from %x (length %d)\n",
                             (void *) ((address_t) buffer + offset),
                             (void *) (elf_header + section_header->offset),
                             size);
                debug_memory_dump ((void *) (((address_t) elf_header) +
                                             section_header->offset),
                                   size / 4);
#endif         
                memory_copy ((void *) ((address_t) buffer + offset),
                             (void *) (((address_t) elf_header) +
                                       section_header->offset), size);
#if DEBUG
                debug_memory_dump ((void *) (((address_t) elf_header) + 
                                             section_header->offset),
                                   size / 4);
#endif
                
                remaining_size -= size;
                file_offset += size;
                page_offset++;
            }
            
            /* We have to take it one page at a time. */
            while (remaining_size > 0)
            {
                /* If this section overlaps another section, find the
                   physical addres of the page that has already been
                   mapped at this place. */
                unsigned int flags;
                page_number_t page_number;
                return_value = memory_virtual_find (page_directory, PAGE_NUMBER (section_header->address), &page_number, &flags);

                /* If it was found, use it instead of overwriting it. */
                if (return_value == STORM_RETURN_SUCCESS)
                {
                    buffer = (void *) (page_number * PAGE_SIZE);
                }
                else
                {
                    /* Allocate memory for this section and map it at the
                       right place. */
                    return_value = memory_physical_allocate (&buffer, 1, process_id);
                    if (return_value != STORM_RETURN_SUCCESS)
                    {
                        debug_print ("Failed to allocate memory");
                        return return_value;
                    }
                    
                    /* Map this memory at the right place. */
                    // FIXME: Get some of the flags from the section (like
                    // writable).
                    return_value = memory_virtual_map
                        (page_directory, 
                         PAGE_NUMBER (section_header->address) + page_offset,
                         PAGE_NUMBER (buffer), 1, PAGE_WRITABLE |
                         PAGE_NON_PRIVILEGED | PAGE_WRITE_THROUGH);
                    if (return_value != STORM_RETURN_SUCCESS)
                    {
                        debug_print ("Failed to map memory");
                        return return_value;
                    }
                }

                /* Copy this page from the image. Another way to do
                   this would be to copy all the section in one sweep,
                   but that would require us to change the CR3 to
                   page_directory or map it in the current
                   process. Either way is most certainly much slower
                   than this, since it needs to flush the cache... */

                size_t length;
                if (remaining_size < PAGE_SIZE)
                {
                    length = remaining_size;
                }
                else
                {
                    length = PAGE_SIZE;
                }

                debug_print ("Copying to %x from %x (%d bytes)\n",
                             buffer, 
                             (void *) (elf_header + section_header->offset + 
                                       file_offset), length);
                memory_copy (buffer, 
                             (void *) (elf_header + section_header->offset + 
                                       file_offset), length);
                remaining_size -= length;
                file_offset += length;
                page_offset++;
            }
        }
    }
  
    return STORM_RETURN_SUCCESS;
}

/* Run the ELF binary at the given address (as a user binary). We only
   have to support static images at the moment so it's incredibly
   simple actually... :) */
static return_t elf_run (void *buffer)
{
    return_t return_value;
    elf_header_t *elf_header = (elf_header_t *) buffer;
    process_id_t process_id;
    void *page_directory;

    /* Make sure this is a valid ELF. */
    return_value = elf_identify (elf_header);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("Invalid ELF.\n");
        return return_value;
    }

    /* Seems to be a valid ELF! We try and load it. But first, we need
       the kernel set up some things for us:

         1) a page directory (for mapping)
         2) a process ID (for allocating memory) 

       This is done by the very nice kernel function
       process_precreate. We have done it this way so that adding
       support for another binary format is incredibly
       simple. Ideally, it should not even require a reboot of the
       system. */
    return_value = process_precreate (&process_id, &page_directory);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed precreating process.\n");
        return return_value;
    }
   
    /* Allocate pages and copy the sections to this space. */
    return_value = elf_load (elf_header, process_id, page_directory);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed loading ELF.\n");
        return return_value;
    }

    /* Create the process. */
    return_value = process_create (process_id, elf_header->entry_point);
    return return_value;
}

/* Return some information about the exec service. */
static return_t service_info (void *exec_void)
{
    exec_service_t *exec = (exec_service_t *) exec_void;

    exec->run = elf_run;
    return STORM_RETURN_SUCCESS;
}

/* The module entry point. */
return_t module_start (void)
{
    /* Create the service. */    
    service_register_t service_register_info;
    service_register_info.vendor = "chaos development";
    service_register_info.model = "ELF loader";
    service_register_info.device_id = "1";
    service_register_info.info_handler = &service_info;

    // FIXME: Fill in this structure.
    service_method_t service_method[] =
        {
            { -1, NULL }
        };

    return exec_register (&service_register_info, service_method);
}
