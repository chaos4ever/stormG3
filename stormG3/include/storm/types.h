/* $chaos: types.h,v 1.13 2002/10/24 21:36:22 per Exp $ */
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
typedef int size_t;

/**
 * @brief               A return value (STORM_RETURN_*) 
 */
typedef int return_t;

/**
 * @brief               A function pointer. 
 */
typedef return_t (*function_t)(void);   /* Can be used even if the
                                           function uses arguments. */

/**
 * @brief               An IRQ handler.
 */
typedef void (irq_handler_t)(unsigned int irq_level);

/**
 * @brief               A unique process ID.
 */
typedef unsigned int    process_id_t;

/**
 * @brief               Type definitions. 
 */
typedef unsigned int    thread_id_t;

/**
 * @brief               A boolean value.
 */
typedef int bool;                       /* no _t, since this should
                                           really have been a built-in
                                           type in C. */

/**
 * @brief                               A function that provides info about
 *                                      this service provider. The data
 *                                      returned is protocol specific.
 */
typedef return_t (*service_info_t)(void *);

/**
 * @brief               A structure used for returning information to the
 *                      caller of service_resolve()
 */
typedef struct
{
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
    char                id[SERVICE_ID_LENGTH];

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

#endif /* !__STORM_TYPES_H__ */
