/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Module support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/ia32/debug.h>
#include <storm/ia32/elf.h>
#include <storm/ia32/module.h>
#include <storm/ia32/multiboot.h>
#include <storm/return_value.h>

/* Link the given shared module into the kernel. */
static return_t module_link (elf_header_t *elf_header)
{
    elf_program_header_t *program_header;
    elf_section_header_t *section_header;
    elf_section_header_t *symbol_header = NULL;
    char *string_table = NULL;
    elf_symbol_t *symbol;

    /* First of all, make sure this is an ELF image... */
    if (!(elf_header->identification[0] == 0x7F &&
          elf_header->identification[1] == 'E' && 
          elf_header->identification[2] == 'L' &&
          elf_header->identification[3] == 'F'))
    {
        return STORM_RETURN_MODULE_INVALID;
    }

    /* ...and a 32-bit one, little-endian, relocatable... */
    if (elf_header->class != ELF_CLASS_32BIT ||
        elf_header->endian != ELF_ENDIAN_LITTLE ||
        elf_header->type != ELF_TYPE_DYNAMIC ||
        elf_header->version != ELF_VERSION_CURRENT ||
        elf_header->machine != ELF_MACHINE_386)
    {
        return STORM_RETURN_MODULE_INVALID;
    }

    /* Find the address of the symbol module_start, and pass control
       on to it. */
    for (int index = 0; index < elf_header->program_header_entries; index++)
    {
        program_header = (elf_program_header_t *) (((uint32_t) elf_header) + elf_header->program_header_offset + (index * elf_header->program_header_entry_size));

    }

    /* Find the string table. */
    for (int index = 0; index < elf_header->section_header_entries; index++)
    {
        section_header = (elf_section_header_t *) (((uint32_t) elf_header) + elf_header->section_header_offset + (index * elf_header->section_header_entry_size));
        if (section_header->type == ELF_SECTION_TYPE_STRING_TABLE &&
            section_header->flags & ELF_SECTION_FLAG_ALLOCATE)
        {
            string_table = (char *) (((uint32_t) elf_header) + section_header->offset);
            debug_print ("%x\n", string_table);
        }
        else if (section_header->type == ELF_SECTION_TYPE_DYNAMIC_SYMBOL_TABLE)
        {
            symbol_header = section_header;
        }
    }

    /* If we don't have a string table and symbol table, we won't be
       able to link this module into the kernel. */
    if (string_table == NULL || symbol_header == NULL)
    {
        return STORM_RETURN_MODULE_INVALID;
    }

    for (int symbol_index = 0; symbol_index * sizeof (elf_symbol_t) <
             symbol_header->size; symbol_index++)
    {
        symbol = (elf_symbol_t *) (((uint32_t) elf_header) + symbol_header->offset + symbol_index * sizeof (elf_symbol_t));
        if (symbol->type == ELF_SYMBOL_TYPE_NONE)
        {
            continue;
        }
        
        debug_print ("symbol type: %u, name: %s (%u), value: %x\n",
                     symbol->type, string_table + symbol->name,
                     symbol->name, symbol->value);
    }

    return STORM_RETURN_SUCCESS;
}

/* Initialize module support. */
void module_init (void)
{
    if (multiboot_info.has_module_info == 1)
    {
        /* Check what modules GRUB has provided for us. */
        for (unsigned int counter = 0; 
             counter < multiboot_info.number_of_modules; counter++) 
        {
            if (module_link ((elf_header_t *) multiboot_module_info[counter].start) != 
                STORM_RETURN_SUCCESS)
            {
                debug_print ("Starting module %s failed.\n",
                             multiboot_module_info[counter].name);
            }
        }
    }
}
