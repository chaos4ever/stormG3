/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Video library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <video/video.h>

/* Get a connection to the video service provider. */
return_t video_init (video_service_t *video)
{
    size_t services;
    service_t *service;

    /* Find the log service. */
    if (service_resolve ("video", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to resolve video service provider.\n");
        return VIDEO_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (video);

    // FIXME: Free the memory allocated by service_resolve.

    return VIDEO_RETURN_SUCCESS;
}
