/* $chaos: video.c,v 1.7 2002/12/03 14:46:16 johannes Exp $ */
/* Abstract: Video library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <video/video.h>

/* Get a connection to the video service provider. */
// FIXME: Take a service_lookup_t as parameter as well.
return_t video_lookup (video_service_t *video)
{
    size_t services = 1;
    service_t service;
    service_lookup_t lookup =
        {
            "video",    /* protocol_name */
            NULL,       /* service_vendor */
            NULL,       /* device_vendor */
            NULL,       /* model */
            NULL,       /* device_id */
            VIDEO_PROTOCOL_MAJOR_VERSION,       /* major version */
            VIDEO_PROTOCOL_MINOR_VERSION,       /* minor version */
        };

    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup video service provider.\n");
        return VIDEO_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (video);

    // FIXME: Free the memory allocated by service_lookup.

    return VIDEO_RETURN_SUCCESS;
}

/* Register a video service provider. */
return_t video_register (service_register_t *service_register_info,
                         service_method_t *service_method)
{    
    service_register_info->protocol_name = "video";
    service_register_info->major_version = VIDEO_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = VIDEO_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
