/* $chaos: service.h,v 1.1 2002/06/20 22:41:00 per Exp $ */
/* Abstract: Service support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_SERVICE_H__
#define __STORM_IA32_SERVICE_H__

#include <storm/storm.h>
#include <storm/ia32/types.h>

/* Definitions. */
#define SERVICE_MAX_NAME_LENGTH         32
#define SERVICE_MAX_VENDOR_LENGTH       32
#define SERVICE_MAX_MODEL_LENGTH        32
#define SERVICE_MAX_ID_LENGTH            16

/* Type definitions. */
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
    function_t handler;

    /* A pointer to the next service. */
    struct service_t *next;
} service_t;

#endif /* !__STORM_IA32_SERVICE_H__ */
