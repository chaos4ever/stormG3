/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Boot module. The boot module takes care of setting up the
   system (opening virtual consoles, launching programs, etc). */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <console/console.h>
#include <log/log.h>
#include <storm/storm.h>

/* The log service provider that we are using. */
log_service_t log;

/* The console service provider that we are using. */
console_service_t console;

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

    // TODO:
    /* Run system initialization (start daemons etc). */
    /* Open virtual consoles. */
    /* Launch the programs assigned to each console. */

    log.print (LOG_URGENCY_INFORMATIVE, "System startup complete.");

    return STORM_RETURN_SUCCESS;
}
