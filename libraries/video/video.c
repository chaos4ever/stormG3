/* $chaos: video.c,v 1.2 2002/08/09 05:59:42 per Exp $ */
/* Abstract: Video library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <video/video.h>

/* Get a connection to the video service provider. */
return_t video_lookup (video_service_t *video)
{
    size_t services;
    service_t *service;

    /* Find the log service. */
    if (service_lookup ("video", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup video service provider.\n");
        return VIDEO_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (video);

    // FIXME: Free the memory allocated by service_lookup.

    return VIDEO_RETURN_SUCCESS;
}
