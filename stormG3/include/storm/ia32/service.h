/* $chaos: service.h,v 1.12 2002/10/28 07:44:33 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                service.h
 * @brief               Services implementation header.
 */

#ifndef __STORM_IA32_SERVICE_H__
#define __STORM_IA32_SERVICE_H__

#include <storm/storm.h>

/**
 * @brief               Information about a service provider. 
 */
typedef struct
{
    /**
     * @brief           A unique service provider ID.
     */
    service_id_t        id;

    /**
     * @brief           The service name. 
     */
    char                name[SERVICE_NAME_LENGTH];

    /**
     * @brief           The vendor name. 
     */
    char                vendor[SERVICE_VENDOR_LENGTH];

    /**
     * @brief           The model name. 
     */
    char                model[SERVICE_MODEL_LENGTH];

    /**
     * @brief           A unique ID for this device.

     * Can be something like a MAC address, serial number, etc. Used
     * to distinguish between different devices with the same model.
     */
    char                device_id[SERVICE_ID_LENGTH];

    /**
     * @brief           The major version of the service provided. 
     */
    unsigned int        major_version;

    /**
     * @brief           The minor version of the service provided.
     */
    unsigned int        minor_version;

    /**
     * @brief           A function that the caller use to get information
     *                  about this service provider. 
     */
    service_info_t      service_info;

    /**
     * @brief           A pointer to the next service. 
     */
    struct service_data_t
                        *next;
} service_data_t;

#endif /* !__STORM_IA32_SERVICE_H__ */
