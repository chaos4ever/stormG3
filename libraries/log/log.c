/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Log library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <log/log.h>

/* Get a connection to the log service provider. */
return_t log_init (log_service_t *log)
{
    log_init_t handler;

    /* Find the log service. */
    if (service_resolve ("log", 1, (function_t *) &handler) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to resolved log service provider.\n");
        return LOG_RETURN_SERVICE_UNAVAILABLE;
    }
    handler (log);

    return LOG_RETURN_SUCCESS;
}
