/* $chaos: boot.c,v 1.3 2002/07/10 21:56:58 per Exp $ */
/* Abstract: Boot module. The boot module takes care of setting up the
   system (opening virtual consoles, launching programs, etc). */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <block/block.h>
#include <console/console.h>
#include <log/log.h>
#include <vfs/vfs.h>

/* The log service provider we are using. */
log_service_t log;

/* The console service provider we are using. */
console_service_t console;

/* The ID of the console that we have opened. */
console_id_t console_id;

/* The block service provider we are using, for mounting the root
   file system. */
block_service_t block;

/* The virtual filesystem service provider we are using. */
vfs_service_t vfs;

/* Entry point. */
return_t module_start (void)
{
    return_t return_value;
    vfs_file_handle_t handle;

    /* Make sure we have a log service provider. */
    if (log_init (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    /* Make sure we have a console service provider. */
    if (console_init (&console) != CONSOLE_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "No console service found. Aborting.");
        return STORM_RETURN_NOT_FOUND;
    }

    /* Make sure we have a block service provider. */
    if (block_resolve (&block) != BLOCK_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "No block service found. Aborting.");
        return STORM_RETURN_NOT_FOUND;
    }

    /* Make sure we have a virtual filesystem provider. */
    if (vfs_resolve (&vfs) != VFS_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "No virtual filesystem service found. Aborting.");
        return STORM_RETURN_NOT_FOUND;
    }
    
    /* Mount the root file system. */
    return_value = vfs.mount ("//", &block);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Mounting file system failed.");
        return return_value;
    }

    /* Assign it to the logical root as well. */
    return_value = vfs.assign ("//", "/");
    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Assigning file system failed.");
        return return_value;
    }

    /* Open a file in the root directory. */
    return_value = vfs.open ("/AreYouExcited.mod", &handle);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Opening file failed.");
        return return_value;
    }

    /* Close the file. */
    return_value = vfs.close (handle);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Closing file failed.");
        return return_value;
    }

    // TODO:
    /* Run system initialization (start daemons etc). */
    /* Open virtual consoles. FIXME: Read a list from somewhere to
       know what consoles to open. If that list cannot be found, use
       some reasonable default. */
#ifdef CONSOLE
    console.open (&console_id, 0, 0, 0, CONSOLE_MODE_TEXT);
    console.output (console_id, "\e[1;37;44mSystem startup complete. åäö is working!\e[K");
#endif

    /* Launch the programs assigned to each console. */
    return STORM_RETURN_SUCCESS;
}
