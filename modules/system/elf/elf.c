/* $chaos: elf.c,v 1.4 2002/10/09 08:31:25 per Exp $ */
/* Abstract: ELF module, implementing the exec service. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <exec/exec.h>

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
                          page_directory_t *page_directory)
{
    //    return_t return_value;
    //    void *image;

    // FIXME: Rewrite this code from scratch, it's not usable in the
    // process ELF execution.
    /* Find the highest end address of a section. This presumes that
       the sections come right after each other, which is a reasonable
       presumption since we control ELF generation for our OS. */
    for (int index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = (elf_section_header_t *) (((uint32_t) elf_header) + elf_header->section_header_offset + (index * elf_header->section_header_entry_size));
        if (section_header->flags & ELF_SECTION_FLAG_ALLOCATE)
        {
            void *buffer; 

            /* We have to take it one page at a time. */
            for (unsigned int page = 0; page < section_header->size; page += PAGE_SIZE)
            {
                /* Allocate memory for this section and map it at the
                   right place. */
                return_t return_value = memory_physical_allocate_for_process (&buffer, process_id);
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
                     PAGE_NUMBER (section_header->address + page),
                     PAGE_NUMBER (buffer), 1, PAGE_WRITABLE |
                     PAGE_NON_PRIVILEGED | PAGE_WRITE_THROUGH);
                if (return_value != STORM_RETURN_SUCCESS)
                {
                    debug_print ("Failed to map memory");
                    return return_value;
                }
            }
            
            /* Copy the data from the image. */
            memory_copy ((void *) section_header->address,
                         (void *) (((address_t) elf_header) +
                                   section_header->offset),
                         section_header->size);
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
    page_directory_t *page_directory;

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
static return_t exec_info (void *exec_void)
{
    exec_service_t *exec = (exec_service_t *) exec_void;

    exec->run = elf_run;
    return STORM_RETURN_SUCCESS;
}

/* The module entry point. */
return_t module_start (void)
{
    return exec_register ("chaos development", "ELF loader", "1", &exec_info);
}
