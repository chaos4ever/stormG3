/* $chaos: initial_ramdisk.c,v 1.10 2002/11/21 21:48:44 per Exp $ */
/* Abstract: Initial ramdisk server. */
/* Authors: Henrik Hallin <hal@chaosdev.org>
            Per Lundberg <per@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <block/block.h>
#include <log/log.h>
#include <memory/memory.h>

#include "ramdisk.h"

/* Define as TRUE if you are debugging this server. */
#undef DEBUG

/* The log service we are using. */
log_service_t log;

/* Read data from this block device. */
static return_t block_read (unsigned int starting_block,
                            unsigned int blocks, void *output)
{
    memory_copy (output, (void *) (ramdisk + (starting_block * RAMDISK_BLOCK_SIZE)),
                 blocks * RAMDISK_BLOCK_SIZE);
    return STORM_RETURN_SUCCESS;
}

/* Write data to this block device. */
static return_t block_write (unsigned int starting_block, unsigned int blocks,
                             void *input)
{
    memory_copy ((void *) (ramdisk + (starting_block * RAMDISK_BLOCK_SIZE)), input, 
                 blocks * RAMDISK_BLOCK_SIZE);
                 
    return STORM_RETURN_SUCCESS;
}

/* Get information about this block device. */
static return_t block_info (block_info_t *info)
{
    info->block_size = RAMDISK_BLOCK_SIZE;
    info->block_count = ramdisk_block_count;
    return STORM_RETURN_SUCCESS;
}

/* Return some information about the block service (function pointers to
   our functionality). */
static return_t service_info (void *block_void)
{
    block_service_t *block = (block_service_t *) block_void;
    block->read = &block_read;
    block->write = &block_write;
    block->info = &block_info;
    return STORM_RETURN_SUCCESS;
}

/* Main function. */
return_t module_start (void)
{
    if (log_lookup (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }
  
    /* Create the service. */
    service_register_t service_register_info;
    service_register_info.service_vendor = "chaos development";
    service_register_info.model = "Initial ramdisk";
    service_register_info.device_id = "1";
    service_register_info.info_handler = &service_info;

    // FIXME: Add our methods here so this service provider can be
    // used from userspace.
    service_method_t service_method[] =
        {
            { -1, NULL }
        };

    return block_register (&service_register_info, service_method);
}
