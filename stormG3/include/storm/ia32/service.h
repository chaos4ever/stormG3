/* $chaos: service.h,v 1.9 2002/10/09 13:07:24 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file service.h
 * @brief Service support. 
 */

#ifndef __STORM_IA32_SERVICE_H__
#define __STORM_IA32_SERVICE_H__

#include <storm/ia32/types.h>

/**
 * @brief The length of a service name.
 */
#define SERVICE_NAME_LENGTH             32

/**
 * @brief The length of a vendor name.
 */
#define SERVICE_VENDOR_LENGTH           32

/**
 * @brief The length of a model name.
 */
#define SERVICE_MODEL_LENGTH            32

/**
 * @brief The length of a unique service ID.
 */
#define SERVICE_ID_LENGTH               16

/**
 * @brief A function that provides info about this service
 * provider. The data returned is protocol specific.
 */
typedef return_t (*service_info_t)(void *);

/**
 * @brief Information about a service provider. 
 */
typedef struct
{
    /**
     * @brief The service name. 
     */
    char name[SERVICE_NAME_LENGTH];

    /**
     * @brief The vendor name. 
     */
    char vendor[SERVICE_VENDOR_LENGTH];

    /**
     * @brief The model name. 
     */
    char model[SERVICE_MODEL_LENGTH];

    /**
     * @brief A unique ID for this device. (MAC address, serial
     * number, etc) Used to distinguish between different devices with
     * the same model. 
     */
    char id[SERVICE_ID_LENGTH];

    /**
     * @brief The version of the service provided. 
     */
    unsigned int version;

    /**
     * @brief A function that the caller use to get information about
     * this service provider. 
     */
    service_info_t service_info;

    /**
     * @brief A pointer to the next service. 
     */
    struct service_data_t *next;
} service_data_t;

/**
 * @brief A structure used for returning information to the caller. 
 */
typedef struct
{
    /**
     * @brief The service name. 
     */
    char name[SERVICE_NAME_LENGTH];

    /**
     * @brief The vendor name. 
     */
    char vendor[SERVICE_VENDOR_LENGTH];

    /**
     * @brief The model name. 
     */
    char model[SERVICE_MODEL_LENGTH];

    /**
     * @brief unique ID for this device. (MAC address, serial number,
     * etc) Used to distinguish between different devices with the
     * same model. 
     */
    char id[SERVICE_ID_LENGTH];

    /**
     * @brief The version of the service provided. 
     */
    unsigned int version;

    /**
     * @brief A function that the caller use to get information about this
     * service provider. 
     */
    service_info_t service_info;
} service_t;

/**
 * @brief Register a service provider. 
 */
extern return_t service_register (char *name, char *vendor, char *model, 
                                  char *id, unsigned int version,
                                  service_info_t service_info);

/**
 * @brief Unregister a service provider. 
 */
extern return_t service_unregister (char *service, function_t handler);

/** 
 * @brief Lookup a service. 
 */
extern return_t service_lookup (char *name, char *vendor, char *model,
                                char *id, unsigned int version, 
                                size_t *services, service_t **service);

#endif /* !__STORM_IA32_SERVICE_H__ */
