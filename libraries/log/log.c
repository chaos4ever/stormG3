/* $chaos: log.c,v 1.2 2002/06/24 21:36:56 per Exp $ */
/* Abstract: Log library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <log/log.h>

/* Get a connection to the log service provider. */
return_t log_init (log_service_t *log)
{
    size_t services;
    service_t *service;

    /* Find the log service. */
    if (service_resolve ("log", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to resolve log service provider.\n");
        return LOG_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (log);

    return LOG_RETURN_SUCCESS;
}