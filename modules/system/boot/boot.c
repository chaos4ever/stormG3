/* $chaos: boot.c,v 1.6 2002/10/04 21:22:24 per Exp $ */
/* Abstract: Boot module. The boot module takes care of setting up the
   system (opening virtual consoles, launching programs, etc). */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <block/block.h>
#include <checksum/checksum.h>
#include <console/console.h>
#include <exec/exec.h>
#include <log/log.h>
#include <memory/memory.h>
#include <vfs/vfs.h>

/* The number of consoles that we are opening. */
#define CONSOLES        2

/* The log service provider we are using. */
log_service_t log;

/* The console service provider we are using. */
console_service_t console;

/* The ID of the console that we have opened. */
console_id_t console_id[CONSOLES];

/* The block service provider we are using, for mounting the root
   file system. */
block_service_t block;

/* The virtual filesystem service provider we are using. */
vfs_service_t vfs;

/* The exec service provider we are using. */
exec_service_t exec;

/* Entry point. */
return_t module_start (void)
{
    return_t return_value;
    vfs_file_handle_t handle;

    /* Make sure we have a log service provider. */
    if (log_lookup (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }

    /* Make sure we have a console service provider. */
    if (console_lookup (&console) != CONSOLE_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "No console service found. Aborting.");
        return STORM_RETURN_NOT_FOUND;
    }

    /* Make sure we have a block service provider. */
    if (block_lookup (&block) != BLOCK_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "No block service found. Aborting.");
        return STORM_RETURN_NOT_FOUND;
    }

    /* Make sure we have a virtual filesystem provider. */
    if (vfs_lookup (&vfs) != VFS_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "No virtual filesystem service found. Aborting.");
        return STORM_RETURN_NOT_FOUND;
    }

    /* Make sure we have an exec service provider. */
    if (exec_lookup (&exec) != EXEC_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "No exec service found. Aborting.");
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

    /* Run system initialization (start daemons etc). We do this
       through a program called boot. */
    // FIXME: Change the name of this to /system/programs/boot or
    // something like this. I believe the Minix module would have to
    // be patched for this to work, though.
    return_value = vfs.open ("/boot", VFS_FILE_MODE_READ,
                             &handle);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Opening file failed.");
        return return_value;
    }

    vfs_file_info_t file_info;
    return_value = vfs.info ("/boot", &file_info);

    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Getting information about file failed.");
        return return_value;
    }
   
    /* Read the file. */
    uint32_t *buffer;
    return_value = memory_global_allocate ((void **) &buffer, file_info.size);
    memory_set_uint8 ((uint8_t *) buffer, 0, file_info.size);
    return_value = vfs.read (handle, buffer, file_info.size);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Reading from file failed.");
        return return_value;
    }

#if FALSE
    for (int c = 0; c < file_info.size / 4; c++)
    {
        debug_print ("%x ", buffer[c]);
        if (c % 8 == 0 && c != 0)
        {
            debug_print("\n");
        }
    }
    debug_print("\n");

#endif

#if FALSE
    checksum_md5_digest_type digest;
    memory_set_uint8 ((uint8_t *) &digest, 0, 16);
    return_value = checksum_md5 (buffer, file_info.size,
                                 &digest);

    for (int c = 0; c < CHECKSUM_MD5_DIGEST_LENGTH; c++)
    {
        debug_print ("%x ", digest[c]);
    }
    debug_print ("\n");
#endif

    /* Close the file. */
    return_value = vfs.close (handle);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Closing file failed.");
        return return_value;
    }

    /* Run this program. */
    return_value = exec.run (buffer);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Failed to run boot sequence.");
        return return_value;
    }

    // TODO:
    /* Open virtual consoles. FIXME: Read a list from somewhere to
       know what consoles to open. If that list cannot be found, use
       some reasonable default. */
#if FALSE
    console.open (&console_id[0], 0, 0, 0, CONSOLE_MODE_TEXT);
    console.output (console_id[0], "\e[1;37;44mSystem startup complete. åäö is working!\e[K\n");
    console.open (&console_id[1], 0, 0, 0, CONSOLE_MODE_TEXT);
    console.output (console_id[1], "Second console");
#endif

    /* Launch the programs assigned to each console. */
    return STORM_RETURN_SUCCESS;
}
