/* $chaos: types.h,v 1.3 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file ia32/types.h
 * @brief IA32-specific types. 
 */

#ifndef __STORM_IA32_TYPES_H__
#define __STORM_IA32_TYPES_H__

#include <storm/types.h>

/** @brief A linear/physical address. */
typedef uint32_t address_t;

/** @brief A page number. */
typedef uint32_t page_number_t;

#endif /* !__STORM_IA32_TYPES_H__ */
