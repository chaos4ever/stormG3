/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Service support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_SERVICE_H__
#define __STORM_IA32_SERVICE_H__

#include <storm/storm.h>
#include <storm/ia32/types.h>

/* Type definitions. */
typedef struct
{
    /* The service name. */
    char *name;

    /* The version of the service provided. */
    unsigned int version;

    /* A function that the caller use to get information about this
       service provider. */
    function_t handler;

    /* A pointer to the next service. */
    struct service_t *next;
} service_t;

#endif /* !__STORM_IA32_SERVICE_H__ */
