/* $chaos: multiboot.c,v 1.1 2002/05/25 20:09:40 per Exp $ */
/* Abstract: Parse multiboot header. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING.
   reference documentation. */

#include <storm/ia32/defines.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/multiboot.h>
#include <storm/ia32/string.h>

multiboot_info_type multiboot_info;
multiboot_module_info_type multiboot_module_info[MAX_STARTUP_SERVERS];
void *memory_map = (void *) MEMORY_MAP_BASE;

/* Copy off some of the Multiboot data we need, so it won't be
   overwritten. */
void multiboot_init (void)
{
    char *target = (char *) MODULE_NAME_BASE;
    unsigned module;
    
    /* Copy the module parameters. */
    memory_copy (multiboot_module_info, 
                 (multiboot_module_info_type *) multiboot_info.module_base,
                 multiboot_info.number_of_modules *
                 sizeof (multiboot_module_info_type));

    /* First of all, make sure module names and parameters are stored
       in a safe place. Otherwise, we may overwrite them later on in
       the boot process. */
    for (module = 0; module < multiboot_info.number_of_modules; module++)
    {
        string_copy (target, multiboot_module_info[module].name);
        multiboot_module_info[module].name = target;
        target += string_length (target) + 1;
    }
    
    /* Now, save the memory map. */
    memory_copy (memory_map, 
                 (void *) multiboot_info.memory_map_address, 
                 multiboot_info.memory_map_length);
    
    /* Now, lets parse the kernel command line. */
    //  arguments_parse ((u8 *) multiboot_info.command_line, arguments_kernel, 0);
}
