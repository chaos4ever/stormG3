/* $chaos: filesystem.c,v 1.9 2002/12/04 22:15:33 per Exp $ */
/* Abstract: Filesystem library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <filesystem/filesystem.h>

/* Lookup the first filesystem service provider. FIXME: Should be
   able to return a list. */
// FIXME: Take a service_lookup_t parameter (bug #60).
return_t filesystem_lookup (filesystem_service_t *filesystem)
{
    // FIXME: Lame.
    size_t services = 1;
    service_t service;
    service_lookup_t lookup =
        {
            "filesystem",  /* protocol_name */
            NULL,       /* service_vendor */
            NULL,       /* device_vendor */
            NULL,       /* model */
            NULL,       /* device_id */
            FILESYSTEM_PROTOCOL_MAJOR_VERSION,     /* major version */
            FILESYSTEM_PROTOCOL_MINOR_VERSION,     /* minor version */
        };
    
    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup filesystem service provider.\n");
        return FILESYSTEM_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (filesystem);

    return FILESYSTEM_RETURN_SUCCESS;
}

/* Register a filesystem service provider. */
return_t filesystem_register (service_register_t *service_register_info,
                         service_method_t *service_method)
{    
    service_register_info->protocol_name = "filesystem";
    service_register_info->major_version = FILESYSTEM_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = FILESYSTEM_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
