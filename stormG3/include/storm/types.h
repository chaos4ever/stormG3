/* $chaos: types.h,v 1.19 2002/11/15 19:52:25 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org>
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** @file               storm/types.h
    @brief              Architecture-independent storm types. */

#ifndef __STORM_TYPES_H__
#define __STORM_TYPES_H__

#include <stdint.h>
#include <storm/defines.h>

/**
 * @brief               A size. 
 */
typedef int             size_t;

/**
 * @brief               A return value (STORM_RETURN_*) 
 */
typedef int             return_t;

/**
 * @brief               A function pointer. 
 */
typedef return_t        (*function_t)(void);   /* Can be used even if
                                                  the function uses
                                                  arguments. */

/**
 * @brief               An IRQ handler.
 */
typedef void (irq_handler_t)(unsigned int irq_level);

/**
 * @brief               A unique process ID.
 */
typedef unsigned int    process_id_t;

/**
 * @brief               A unique thread ID.
 */
typedef unsigned int    thread_id_t;

/**
 * @brief               A unique service provider ID.
 */
typedef uint64_t        service_id_t;

/**
 * @brief               An ID for a connection to a service provider.
 */
typedef uint64_t        service_connection_id_t;

/**
 * @brief               An ID for a method in a protocol.
 */
typedef unsigned int    service_method_id_t;

/**
 * @brief               A boolean value.
 */
typedef int             bool;        /* no _t, since this should
                                        really have been a built-in
                                        type in C. */

/**
 * @brief               A function that provides info about
 *                      this service. The data returned is
 *                      protocol specific.
 */
typedef return_t (*service_info_t)(void *);

/**
 * @brief               A function provided by a service.
 */
typedef return_t (*service_function_t)(service_id_t service_id, void *data);

/**
 * @brief               A structure used for returning information to the
 *                      caller of service_resolve()
 */
typedef struct
{
    /**
     * @brief           The service provider ID.
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
     * @brief           Unique ID for this device. (MAC address, serial
     *                  number, etc). Used to distinguish between 
     *                  different devices with the same model. 
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
} service_t;

/**
 * @brief               This structure is used when looking up services.
 */
typedef struct
{
    /**
     * @brief           The name of the service.
     */
    const char          *name;

    /**
     * @brief           The vendor of the service provider OR device. 
     *                  FIXME: We need to take care of this ambiguity.
     */
    const char          *vendor;

    /**
     * @brief           The model of the device.
     */
    const char          *model;

    /**
     * @brief           Unique ID for this device. 
     */
    const char          *device_id;

    /**
     * @brief           The major version of the service provided.
     */
    unsigned int        major_version;

    /**
     * @brief           The minor version of the service provided.
     */
    unsigned int        minor_version;
} service_lookup_t;

/**
 * @brief               This structure is used when registering a service.
 */
typedef struct
{
    /**
     * @brief           The name of the service provided.
     */
    const char          *service_name;

    /**
     * @brief           The vendor of the service provider OR device. 
     *                  FIXME: We need to take care of this ambiguity.
     */
    const char          *vendor;

    /**
     * @brief           The model of the device.
     */
    const char          *model;

    /**
     * @brief           Unique ID for this device. 
     */
    const char          *device_id;

    /**
     * @brief           The major version of the service provided.
     */
    unsigned int        major_version;

    /**
     * @brief           The minor version of the service provided.
     */
    unsigned int        minor_version;

    /**
     * @brief           An handler for returning information about this
     *                  service provider (protocol-specific).
     */
    service_info_t      info_handler;
} service_register_t;

/**
 * @brief               This structure is used for registering the methods
 *                      in a service provider.
 */
typedef struct
{
    /**
     * @brief           A protocol-specific number assigned to this method.
     */
    service_method_id_t method_id;

    /**
     * @brief           A pointer to the method handler.
     */
    service_function_t  method;
} service_method_t;

#endif /* !__STORM_TYPES_H__ */
