/* $chaos: elf.c,v 1.2 2002/10/04 19:01:13 per Exp $ */
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

/* Run the ELF binary at the given address (as a user binary). We only
   have to support static images at the moment so it's incredibly
   simple actually... :) */
static return_t elf_run (void *buffer)
{
    elf_header_t *elf_header = (elf_header_t *) buffer;

    /* Make sure the ELF is valid. */
    return_t return_value = elf_identify (elf_header);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    /* Allocate memory for the different sections. */
    /* Copy the sections. */
    /* Create the proces with the kernel. */
    return STORM_RETURN_SUCCESS;
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
