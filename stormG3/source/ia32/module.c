/* $chaos: module.c,v 1.24 2002/10/09 09:23:33 per Exp $ */
/* Abstract: Module support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/ia32/debug.h>
#include <storm/ia32/dma.h>
#include <storm/ia32/elf.h>
#include <storm/ia32/halt.h>
#include <storm/ia32/irq.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/module.h>
#include <storm/ia32/multiboot.h>
#include <storm/ia32/service.h>
#include <storm/ia32/string.h>
#include <storm/ia32/timer.h>
#include <storm/return_value.h>

/* A list of functions provided through dynamic linking to kernel
   modules. We could export everything, but we don't want to do that
   to keep the API clean. */
static module_function_t function[] = 
{
    { "debug_print", (function_t) &debug_print },

    { "dma_register", (function_t) &dma_register },
//  { "dma_unregister", (function_t) &dma_unregister },

    { "halt", (function_t) &halt },

    { "irq_register", (function_t) &irq_register },
//  { "irq_unregister", (function_t) &irq_unregister }

    { "memory_global_allocate", (function_t) &memory_global_allocate },
    { "memory_global_deallocate", (function_t) &memory_global_deallocate },

    { "module_register", (function_t) &module_register },
//  { "module_unregister", (function_t) &module_unregister },

    { "port_range_register", (function_t) &port_range_register },
//  { "port_range_unregister", (function_t) &port_range_unregister },

//  { "process_precreate", (function_t) &process_precreate },
//  { "process_create", (function_t) &process_create },

    { "service_register", (function_t) &service_register },
//  { "service_unregister", (function_t) &service_unregister },
    { "service_lookup", (function_t) &service_lookup },

    { "timer_sleep_milli", (function_t) &timer_sleep_milli },
    { NULL, (function_t) NULL } /* End of list. */
};

/* Link the given shared module into the kernel. */
static return_t module_link (elf_header_t *elf_header)
{
    volatile return_t return_value;
    elf_parsed_t elf_parsed;
    function_t module_start = NULL;

    memory_set_uint8 ((uint8_t *) &elf_parsed, 0, sizeof (elf_parsed_t));

    /* Find the address of the symbol module_start, and pass control
       on to it. */
    return_value = elf_parse (elf_header, &elf_parsed);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Allocate pages and copy the sections to this space. */
    return_value = elf_load (&elf_parsed);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed loading ELF.\n");
        return return_value;
    }

    /* Try and resolve unresolved symbols */
    return_value = elf_resolve (&elf_parsed, function);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed resolving unresolved symbols.\n");
        return return_value;
    }

    /* Relocate relocatable symbols (all kernel functions this module
       is accessing). */
    return_value = elf_relocate (&elf_parsed);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed relocating ELF.\n");
        return return_value;
    }

    // FIXME: Call the function module_info to get module name and
    // version from the module. This information should be added into
    // a linked list of all the modules.
    /* Everything seems to be fine. Now, we call module_start. */
    return_value = elf_symbol_find_by_name (&elf_parsed, "module_start", (address_t *) &module_start);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to find the module_start symbol.\n");
        return return_value;
    }

    /* Call the module entry point. */
    return_value = module_start ();

    // FIXME: If return_value != STORM_RETURN_SUCCESS, run module_stop.

    return return_value;
}

/* Initialize module support. */
void module_init (void)
{
    if (multiboot_info.has_module_info == 0 || 
        multiboot_info.number_of_modules == 0)
    {
        debug_print ("Warning: No modules loaded. This system will not be usable.\n");
    }
    else
    {
        /* Check what modules GRUB has provided for us. */
        for (unsigned int counter = 0; 
             counter < multiboot_info.number_of_modules; counter++) 
        {
            debug_print ("Starting module %s.\n",
                         multiboot_module_info[counter].name);
            if (module_link ((elf_header_t *) multiboot_module_info[counter].start) != STORM_RETURN_SUCCESS)
            {
                debug_print ("Starting module %s failed.\n",
                             multiboot_module_info[counter].name);
            }
            else
            {
                /* Free the memory used by the ELF image. */
                for (unsigned int page_number = multiboot_module_info[counter].start / PAGE_SIZE; page_number < multiboot_module_info[counter].end / PAGE_SIZE; page_number++)
                {
                    memory_physical_deallocate ((void *) (page_number * PAGE_SIZE));
                }
            }
        }
    }
}

/* Register a module with the kernel. */
void module_register (void)
{
    debug_print ("%s\n", __FUNCTION__);
}
