/* $chaos: video.c,v 1.4 2002/10/28 08:11:15 per Exp $ */
/* Abstract: Video library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <video/video.h>

/* Get a connection to the video service provider. */
return_t video_lookup (video_service_t *video)
{
    size_t services = 1;
    service_t service;

    /* Find the log service. */
    if (service_lookup ("video", NULL, NULL, NULL, VIDEO_SERVICE_MAJOR_VERSION, VIDEO_SERVICE_MINOR_VERSION, &services, &service) != STORM_RETURN_SUCCESS)
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
    service_register_info->service_name = "video";
    service_register_info->major_version = VIDEO_SERVICE_MAJOR_VERSION;
    service_register_info->minor_version = VIDEO_SERVICE_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
