/* $chaos: initial_ramdisk.c,v 1.1 2002/06/26 06:40:40 per Exp $ */
/* Abstract: Initial ramdisk server. */
/* Authors: Henrik Hallin <hal@chaosdev.org>
            Per Lundberg <per@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <log/log.h>

#include "ramdisk.h"

/* Define as TRUE if you are debugging this server. */
#undef DEBUG

/* The log service we are using. */
log_service_t log;

/* Return some information about the block service (function pointers to
   our functionality). */
static return_t service_info (void *ramdisk_void __attribute__ ((unused)))
{
    return STORM_RETURN_SUCCESS;
}

/* Main function. */
return_t module_start (void)
{
    if (log_init (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }
  
    debug_print ("Blocks: %u\n", blocks);

    /* Create the service. */
    return service_register ("block", "chaos development", "Initial ramdisk",
                             "1", BLOCK_VERSION, &service_info);
                             
}
