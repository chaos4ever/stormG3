/* $chaos: service.h,v 1.3 2002/06/24 21:10:00 per Exp $ */
/* Abstract: Service support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_SERVICE_H__
#define __STORM_IA32_SERVICE_H__

#include <storm/ia32/types.h>

/* Definitions. */
#define SERVICE_MAX_NAME_LENGTH         32
#define SERVICE_MAX_VENDOR_LENGTH       32
#define SERVICE_MAX_MODEL_LENGTH        32
#define SERVICE_MAX_ID_LENGTH           16

/* Type definitions. */
/* A function that provides info about this service provider. The data
   returned is protocol specific. */
typedef return_t (*service_info_t)(void *);

/* This one is used internally in the kernel. */
typedef struct
{
    /* The service name. */
    char name[SERVICE_MAX_NAME_LENGTH];

    /* The vendor name. */
    char vendor[SERVICE_MAX_VENDOR_LENGTH];

    /* The model name. */
    char model[SERVICE_MAX_MODEL_LENGTH];

    /* A unique ID for this device. (MAC address, serial number, etc)
       Used to distinguish between different devices with the same
       model. */
    char id[SERVICE_MAX_ID_LENGTH];

    /* The version of the service provided. */
    unsigned int version;

    /* A function that the caller use to get information about this
       service provider. */
    service_info_t service_info;

    /* A pointer to the next service. */
    struct service_data_t *next;
} service_data_t;

/* This one is used for returning information to the caller (kernel
   module or user process alike). */
typedef struct
{
    /* The service name. */
    char name[SERVICE_MAX_NAME_LENGTH];

    /* The vendor name. */
    char vendor[SERVICE_MAX_VENDOR_LENGTH];

    /* The model name. */
    char model[SERVICE_MAX_MODEL_LENGTH];

    /* A unique ID for this device. (MAC address, serial number, etc)
       Used to distinguish between different devices with the same
       model. */
    char id[SERVICE_MAX_ID_LENGTH];

    /* The version of the service provided. */
    unsigned int version;

    /* A function that the caller use to get information about this
       service provider. */
    service_info_t service_info;
} service_t;

/* Register a service provider. */
extern return_t service_register (char *name, char *vendor, char *model, 
                                  char *id, unsigned int version,
                                  service_info_t service_info);

/* Unregister a service provider. */
extern return_t service_unregister (char *service, function_t handler);

/* Resolve a service. */
extern return_t service_resolve (char *name, char *vendor, char *model,
                                 char *id, unsigned int version, 
                                 size_t *services, service_t **service);

#endif /* !__STORM_IA32_SERVICE_H__ */
