/* $chaos: module.h,v 1.3 2002/07/12 09:43:36 per Exp $ */
/* Abstract: Functions and variables defined by a module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_MODULE_H__
#define __STORM_MODULE_H__

#include <storm/types.h>

/* Defines. */
#define MODULE_NAME_LENGTH              48
#define MODULE_VERSION_LENGTH           16

/* A module information structure. */
typedef struct
{
    /* The module name.*/
    char name[MODULE_NAME_LENGTH];
    
    /* The module version. */
    char version[MODULE_VERSION_LENGTH];
} module_info_t;

#ifndef STORM /* Only when included by a module. */

extern return_t module_start (void);
extern return_t module_info (module_info_t *module_info);
extern char module_name[];

#endif /* !STORM */

#endif /* !__STORM_MODULE_H__ */
