/* $chaos: service.h,v 1.16 2002/11/03 22:26:47 per Exp $ */
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
extern return_t         service_connect (service_id_t service_id,
                                         service_connection_id_t *connection_id);

/**
 * @brief               Close a connection that has been made to a service
 *                      provider.
 * @param connection_id The ID of the connection.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t         service_close (service_connection_id_t connection_id);

/**
 * @brief               Invoke a function with a service provider.
 * @param connection_id The connection ID of the connection we have with the
 *                      service provider.
 * @param function_number
 *                      The number of the function to run with this service
 *                      provider.
 * @param data          The data to the function.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t         service_invoke (service_connection_id_t connection_id,
                                        unsigned int function_number,
                                        void *data);

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
     * @brief           A reference count of this service provider.
     */
    unsigned int        reference_count;

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
     *
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

/**
 * @brief               A connection by a process to a service.
 */
typedef struct
{
    /**
     * @brief           A pointer to the previous connection.
     */
    struct service_connection_t
                        *previous;

    /**
     * @brief           A pointer to the next connection.
     */
    struct service_connection_t
                        *next;
    
    /**
     * @brief           A connection ID.
     */
    service_connection_id_t
                        id;

    /**
     * @brief           The process that is connected to this service.
     */
    process_t           *process;

    /**
     * @brief           A pointer to the service we are connected to.
     */
    service_data_t      *service;
   
} service_connection_t;

/**
 * @brief               A method handler in a service provider.
 */
typedef struct
{
    /**
     * @brief           Pointer to the previous service method.
     */
    struct service_method_data_t 
                        *previous;

    /**
     * @brief           Pointer to the next service method.
     */
    struct service_method_data_t
                        *next;

    /**
     * @brief           The ID of the service provider providing this
     *                  method.
     */
    service_id_t        service_id;

    /**
     * @brief           The method ID (unique within the protocol) of the
     *                  method handler.
     */
    service_method_id_t method_id;

    /**
     * @brief           The method handler.
     */
    function_t          method;
} service_method_data_t;

#endif /* !__STORM_IA32_SERVICE_H__ */
