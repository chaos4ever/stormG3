/* $chaos: kernel.c,v 1.5 2002/12/03 14:47:39 johannes Exp $ */
/* Abstract: Sound protocol implementation library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             sound.c
 * @brief            Sound protocol implementation library.
 */

#include <sound/sound.h>

/* Lookup the first sound service. */
// FIXME: Should be able to return a list.
return_t sound_lookup (sound_service_t *sound)
{
    // FIXME: Lame.
    size_t services = 1;
    service_t service;

    // FIXME: bug #60.
    service_lookup_t lookup =
        {
            "sound",    /* protocol_name */
            NULL,       /* service_vendor */
            NULL,       /* device_vendor */
            NULL,       /* model */
            NULL,       /* device_id */
            SOUND_PROTOCOL_MAJOR_VERSION,       /* major_version */
            SOUND_PROTOCOL_MINOR_VERSION,       /* minor_version */
        };

    /* Find the sound service. */
    if (service_lookup (&lookup, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup sound service provider.\n");
        return SOUND_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (sound);

    // FIXME: Free the memory allocated by service_lookup.
    return SOUND_RETURN_SUCCESS;
}

/* Register a sound service. */
return_t sound_register (service_register_t *service_register_info,
                         service_method_t *service_method)
{    
    service_register_info->protocol_name = "sound";
    service_register_info->major_version = SOUND_PROTOCOL_MAJOR_VERSION;
    service_register_info->minor_version = SOUND_PROTOCOL_MINOR_VERSION;

    return service_register (service_register_info, service_method);
}
