/* $chaos: service.h,v 1.13 2002/10/29 20:48:01 per Exp $ */
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
 * @brief               Connect to the given service provider.
 * @param service_id    ID of the service provider to connect to.
 * @param connection_id Pointer to where the connection ID will be stored.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t service_connect (service_id_t service_id,
                                 service_connection_id_t *connection_id);

/**
 * @brief               Close a connection that has been made to a service
 *                      provider.
 * @param connection_id The ID of the connection.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t service_close (service_connection_id_t connection_id);

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
