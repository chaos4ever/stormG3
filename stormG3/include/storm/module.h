/* $chaos: module.h,v 1.4 2002/10/04 19:01:19 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file storm/module.h
 * @brief Functions and variables defined by a module. 
 */

#ifndef __STORM_MODULE_H__
#define __STORM_MODULE_H__

#include <storm/types.h>

/* Defines. */
#define MODULE_NAME_LENGTH              48
#define MODULE_VERSION_LENGTH           16

/** 
 * @brief A module information structure. 
 */
typedef struct
{
    /** 
     * @brief The module name.
     */
    char name[MODULE_NAME_LENGTH];
    
    /**
     * @brief The module version. 
     */
    char version[MODULE_VERSION_LENGTH];
} module_info_t;

#ifndef STORM /* Only when included by a module. */

/** 
 * @brief The module entry point. 
 */
extern return_t module_start (void);
//extern return_t module_info (module_info_t *module_info);
//extern char module_name[];

#endif /* !STORM */

#endif /* !__STORM_MODULE_H__ */
