/* $chaos: module.h,v 1.5 2002/10/08 20:14:56 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                storm/module.h
 * @brief               Functions and variables defined by a module. 
 */

#ifndef __STORM_MODULE_H__
#define __STORM_MODULE_H__

#include <storm/types.h>

/* Defines. */
#define MODULE_NAME_LENGTH              48
#define MODULE_VERSION_LENGTH           16

/** 
 * @brief               A module information structure. 
 */
typedef struct
{
    /** 
     * @brief           The module name.
     */
    char                name[MODULE_NAME_LENGTH];
    
    /**
     * @brief           The module version. 
     */
    char                version[MODULE_VERSION_LENGTH];
} module_info_t;

#endif /* !__STORM_MODULE_H__ */
