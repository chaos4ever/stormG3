/* $chaos: log.c,v 1.10 2002/12/03 14:32:48 johannes Exp $ */
/* Abstract: Log library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <log/log.h>

/* Get a connection to the log service provider. */
// FIXME: Take a service_lookup_t parameter.
return_t log_lookup (log_service_t *log)
{
    // FIXME: Lame.
    size_t services = 1;
    service_t service;
    service_lookup_t lookup =
        {
            "log",      /* protocol_name */
            NULL,       /* service_vendor */
            NULL,       /* device_vendor */
            NULL,       /* model */
            NULL,       /* device_id */
            LOG_PROTOCOL_MAJOR_VERSION,         /* major version */
            LOG_PROTOCOL_MINOR_VERSION,         /* minor version */
        };

    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup log service provider.\n");
        return LOG_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (log);

    return LOG_RETURN_SUCCESS;
}

/* Register a log service provider. */
return_t log_register (service_register_t *service_register_info,
                         service_method_t *service_method)
{    
    service_register_info->protocol_name = "log";
    service_register_info->major_version = LOG_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = LOG_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
