/* $chaos: multiboot.c,v 1.5 2002/06/15 15:38:55 per Exp $ */
/* Abstract: Parse multiboot header. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING.
   reference documentation. */

#include <storm/ia32/debug.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/multiboot.h>
#include <storm/ia32/string.h>

multiboot_info_t multiboot_info;
multiboot_module_info_t multiboot_module_info[MAX_STARTUP_SERVERS];
multiboot_memory_map_t multiboot_memory_map[MEMORY_MAP_SIZE];
static char module_name[MODULE_NAME_SIZE];
static char command_line[COMMAND_LINE_SIZE];

/* Copy off some of the Multiboot data we need, so it won't be
   overwritten. */
/* FIXME: This function fails for some really weird reason if the
   machine has less than 32 megabyte of RAM. */
void multiboot_init (void)
{
    char *target = (char *) &module_name;

    /* Make sure we don't get out of bounds. */
    if (multiboot_info.number_of_modules > MAX_STARTUP_SERVERS)
    {
        multiboot_info.number_of_modules = MAX_STARTUP_SERVERS;
    }

    /* Copy the module parameters. */
    memory_copy (multiboot_module_info, 
                 (multiboot_module_info_t *) multiboot_info.module_base,
                 multiboot_info.number_of_modules *
                 sizeof (multiboot_module_info_t));

    /* First of all, make sure module names and parameters are stored
       in a safe place. Otherwise, we may overwrite them later on in
       the boot process. */
    for (unsigned int module = 0; module < multiboot_info.number_of_modules;
         module++)
    {
        if (multiboot_module_info[module].name == NULL) 
        {
            multiboot_module_info[module].name = NULL;
        }
        else
        {
            string_copy (target, multiboot_module_info[module].name);
            multiboot_module_info[module].name = target;
            target += string_length (target) + 1;
        }
    }

    /* Now, save the memory map. */
    memory_copy ((void *) &multiboot_memory_map,
                 (void *) multiboot_info.memory_map_address, 
                 multiboot_info.memory_map_length);

    /* Save the kernel arguments so that we can parse them later
       on. FIXME: Implement this parsing. */
    string_copy_max (command_line, (void *) multiboot_info.command_line, 
                     COMMAND_LINE_SIZE - 1);
}
