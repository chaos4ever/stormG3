/* $chaos: boot.c,v 1.1 2002/06/23 20:42:32 per Exp $ */
/* Abstract: Boot module. The boot module takes care of setting up the
   system (opening virtual consoles, launching programs, etc). */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <block/block.h>
#include <console/console.h>
#include <log/log.h>

/* The log service provider that we are using. */
log_service_t log;

/* The console service provider that we are using. */
console_service_t console;

/* The block service provider that we are using, for mounting the root
   file system. */
block_service_t block;

/* Entry point. */
return_t module_start (void)
{
    /* Contact the log service provider. */
    if (log_init (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    if (console_init (&console) != CONSOLE_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    if (block_resolve (&block) != CONSOLE_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_WARNING,
                   "No block device found. This system will not be usable.");
    }
    else 
    {
        block_info_t info;
        block.info(&info);
        debug_print ("%u %u\n", info.block_size, info.block_count);
    }

    // TODO:
    /* Mount the root file system. */
    /* Run system initialization (start daemons etc). */
    /* Open virtual consoles. */
    /* Launch the programs assigned to each console. */

    log.print (LOG_URGENCY_INFORMATIVE, "System startup complete.");

    return STORM_RETURN_SUCCESS;
}
