/* $chaos: log.c,v 1.4 2002/07/09 08:40:17 per Exp $ */
/* Abstract: Log library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <log/log.h>

/* Get a connection to the log service provider. */
return_t log_lookup (log_service_t *log)
{
    size_t services;
    service_t *service;

    /* Find the log service. */
    if (service_lookup ("log", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup log service provider.\n");
        return LOG_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (log);

    // FIXME: Free the memory allocated by service_lookup.

    return LOG_RETURN_SUCCESS;
}
