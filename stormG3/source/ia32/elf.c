/* $chaos: elf.c,v 1.9 2002/07/04 21:26:56 per Exp $ */
/* Abstract: ELF functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/return_value.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/elf.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/string.h>

/* Make sure this is a valid ELF for our platform. */
return_t elf_identify (elf_header_t *elf_header)
{
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

    return STORM_RETURN_SUCCESS;
}

/* Parse the given ELF header. */
return_t elf_parse (elf_header_t *elf_header, elf_parsed_t *elf_parsed)
{
    /* Make sure the ELF is valid. */
    return_t return_value = elf_identify (elf_header);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    elf_parsed->elf_header = elf_header;

    /* Find the string table and symbol table. */
    for (int index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = (elf_section_header_t *) (((uint32_t) elf_header) + elf_header->section_header_offset + (index * elf_header->section_header_entry_size));
        if (section_header->type == ELF_SECTION_TYPE_STRING_TABLE &&
            section_header->flags & ELF_SECTION_FLAG_ALLOCATE)
        {
            elf_parsed->string_header = section_header;
        }
        else if (section_header->type == ELF_SECTION_TYPE_DYNAMIC_SYMBOL_TABLE)
        {
            elf_parsed->symbol_header = section_header;
        }
        else if (section_header->type == ELF_SECTION_TYPE_RELOCATION)
        {
            elf_parsed->relocation_header = section_header;
        }
    }

    /* If we don't have a string table and symbol table, we won't be
       able to link this module into the kernel. */
    if (elf_parsed->string_header == NULL ||
        elf_parsed->symbol_header == NULL)
    {
        return STORM_RETURN_MODULE_INVALID;
    }

    return STORM_RETURN_SUCCESS;
}

/* Resolve unresolved symbols in the given symbol table. */
return_t elf_resolve (elf_parsed_t *elf_parsed, module_function_t *function)
{
    elf_symbol_t *symbol;
    elf_section_header_t *symbol_header = elf_parsed->symbol_header;
    char *string_table = (char *) (((address_t) elf_parsed->image) +
                                   elf_parsed->string_header->offset);

    /* Work out all unresolved symbols. Symbol index 0 is not used. */
    for (int symbol_index = 1; symbol_index * sizeof (elf_symbol_t) <
             symbol_header->size; symbol_index++)
    {
        symbol = (elf_symbol_t *) (((address_t) elf_parsed->image) + symbol_header->offset + symbol_index * sizeof (elf_symbol_t));

        /* Non-empty value and a section header means we should just
           do simple address translation to our new offset. */
        if (symbol->value != 0 && symbol->section_header != 0)
        {
            symbol->value += (address_t) elf_parsed->image;
        }
        /* Empty value and no section header means unresolved
           symbol. */
        else if (symbol->value == 0 && symbol->section_header == 0)
        {
            char *name = string_table + symbol->name;
            volatile bool match = FALSE;

            for (int function_index = 0; 
                 function[function_index].name != NULL;
                 function_index++)
            {
                if (string_compare (function[function_index].name, name) == 0)
                {
                    /* We have a match. Modify the symbol table. */
                    symbol->value = (uint32_t) function[function_index].function;
                    
                    match = TRUE;
                    break;
                }
            }

            if (match == FALSE)
            {
                debug_print ("Unresolved symbol in module: %s\n",
                             name);
                return STORM_RETURN_MODULE_INVALID;
            }
        }
    }
    
    return STORM_RETURN_SUCCESS;
}

/* Relocate relocatable symbols. */
return_t elf_relocate (elf_parsed_t *elf_parsed)
{
    elf_relocation_t *relocation;
    elf_section_header_t *relocation_header = elf_parsed->relocation_header;
    elf_header_t *elf_header = elf_parsed->elf_header;

    /* Perform relocation. */
    if (elf_parsed->relocation_header == NULL)
    {
        return STORM_RETURN_SUCCESS;
    }
   
    relocation = (elf_relocation_t *) (((uint32_t) elf_header) + elf_parsed->relocation_header->offset);
    for (int index = 0; index * sizeof (elf_relocation_t) <
             relocation_header->size; index++)
    {
        address_t symbol_address;
        address_t *relocation_address;
        return_t return_value = elf_symbol_find_by_index (elf_parsed, relocation[index].symbol_index, &symbol_address);
        if (return_value != STORM_RETURN_SUCCESS)
        {
            return return_value;
        }

        /* Perform this relocation. */
        relocation_address = (address_t *) (((address_t) elf_parsed->image) + relocation[index].offset);
        
        // FIXME: Use defines for these types.
        if (relocation[index].symbol_type == 1)
        {
            *relocation_address = *relocation_address + symbol_address;
        }
        else if (relocation[index].symbol_type == 2)
        {
            /* Are you confused yet? :-) */
            *relocation_address =  *relocation_address + (address_t) (symbol_address - (address_t) relocation_address);
        }
        else if (relocation[index].symbol_type == ELF_RELOCATION_RELATIVE)
        {
            *relocation_address = *relocation_address + (address_t) elf_parsed->image;
        }
        else
        {
            debug_print ("%x %u %u\n",
                         relocation[index].offset,
                         relocation[index].symbol_type,
                         relocation[index].symbol_index);
            debug_print ("Unknown relocation type: %u == %u\n", 
                         relocation[index].symbol_type,
                         relocation[index].symbol_type);
            debug_print ("%x %u %u\n",
                         relocation[index].offset,
                         relocation[index].symbol_type,
                         relocation[index].symbol_index);
            //            return STORM_RETURN_MODULE_INVALID;
        }
    }

    return STORM_RETURN_SUCCESS;
}

/* Find the given symbol in the symbol table. */
return_t elf_symbol_find_by_index (elf_parsed_t *elf_parsed,
                                   unsigned int index,
                                   uint32_t *address)
{
    elf_section_header_t *symbol_header = elf_parsed->symbol_header;
    elf_symbol_t *symbol;

    /* Make sure this symbol exists in the symbol table. */
    if (symbol_header->size / sizeof (elf_symbol_t) < index)
    {
        return STORM_RETURN_MODULE_INVALID;
    }

    symbol = (elf_symbol_t *) (((address_t) elf_parsed->image) + symbol_header->offset + index * sizeof (elf_symbol_t));
    *address = symbol->value;
    return STORM_RETURN_SUCCESS;
}

/* Find the given symbol in the symbol table. */
return_t elf_symbol_find_by_name (elf_parsed_t *elf_parsed,
                                  char *name, uint32_t *address)
{
    elf_section_header_t *symbol_header = elf_parsed->symbol_header;
    char *string_table = (char *) (((address_t) elf_parsed->image) +
                                   elf_parsed->string_header->offset);

    for (int symbol_index = 1; symbol_index * sizeof (elf_symbol_t) <
             symbol_header->size; symbol_index++)
    {
        elf_symbol_t *symbol = (elf_symbol_t *) (((address_t) elf_parsed->image) + symbol_header->offset + symbol_index * sizeof (elf_symbol_t));
        char *symbol_name = string_table + symbol->name;

        if (string_compare (symbol_name, name) == 0)
        {
            *address = symbol->value;
            return STORM_RETURN_SUCCESS;
        }
    }

    return STORM_RETURN_MODULE_INVALID;
}

/* Load an ELF. Allocate memory for it, and copy the data from the
   different sections there. */
return_t elf_load (elf_parsed_t *elf_parsed)
{
    elf_header_t *elf_header = elf_parsed->elf_header;
    address_t highest_address = 0;
    return_t return_value;
    void *image;

    /* Find the highest end address of a section. This presumes that
       the sections come right after each other, which is a reasonable
       presumption since we control ELF generation for our OS. */
    for (int index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = (elf_section_header_t *) (((uint32_t) elf_header) + elf_header->section_header_offset + (index * elf_header->section_header_entry_size));
        if (section_header->flags & ELF_SECTION_FLAG_ALLOCATE &&
            section_header->address + section_header->size > highest_address)
        {
            highest_address = section_header->address + section_header->size;
        }
    }
  
    return_value = memory_physical_allocate (&image, highest_address / PAGE_SIZE + 1);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Now, go through all the sections again, but this time copying
       off all the sections into our new pointer. */
    for (int index = 0; index < elf_header->section_header_entries; index++)
    {
        elf_section_header_t *section_header = (elf_section_header_t *) (((uint32_t) elf_header) + elf_header->section_header_offset + (index * elf_header->section_header_entry_size));
        if (section_header->flags & ELF_SECTION_FLAG_ALLOCATE)
        {
            memory_copy ((void *) (((address_t) image) + section_header->address),
                         (void *) (((address_t) elf_header) + section_header->offset),
                         section_header->size);
        }
    }

    elf_parsed->image = image;

    return STORM_RETURN_SUCCESS;
}

