/* $chaos: types.h,v 1.6 2002/10/15 18:06:30 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                ia32/types.h
 * @brief               IA32-specific types. 
 */

#ifndef __STORM_IA32_TYPES_H__
#define __STORM_IA32_TYPES_H__

#include <storm/types.h>

/**
 * @brief               A linear/physical address. 
 */
typedef                 uint32_t address_t;

/**
 * @brief               A user ID.
 */
typedef                 uint32_t user_id_t;

/**
 * @brief               A group ID.
 */
typedef                 uint32_t group_id_t;

#endif /* !__STORM_IA32_TYPES_H__ */
