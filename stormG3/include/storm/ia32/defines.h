/* $chaos: defines.h,v 1.17 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file        ia32/defines.h
 * @brief       IA32-specific storm defines. 
 */

#ifndef __STORM_IA32_DEFINES_H__
#define __STORM_IA32_DEFINES_H__

#include <storm/defines.h>
#include <storm/types.h>

/**
 * @brief       The size of a physical page. 
 */
#define PAGE_SIZE                       0x1000

/**
 * @brief       The page number of an address, shifted 10 bits to the left.
*/
#define PAGE_ADDRESS(x)                 ((void *) (((uint32_t) x) & 0xFFFFF000))

/**
 * @brief       Size of some regions. 
 */
#define KERNEL_STACK_SIZE               (4 * KIB)

/**
 * @brief       The kernel starts at 1 MiB. 
 */
#define KERNEL_BASE                     (1 * MIB)

/**
 * @brief       The maximum memory amount that we support. 
 */
#define MAX_MEMORY                      ((uint32_t) 2 * GIB)

#endif /* !__STORM_IA32_DEFINES_H__ */
