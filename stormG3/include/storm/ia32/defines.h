/* $chaos: defines.h,v 1.23 2002/10/22 20:56:52 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file                ia32/defines.h
 * @brief               IA32-specific storm defines. 
 */

#ifndef __STORM_IA32_DEFINES_H__
#define __STORM_IA32_DEFINES_H__

#include <storm/defines.h>
#include <storm/types.h>

/* The defines in this file are not for user-level programs. */
#if (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__)

/**
 * @brief               The size of a physical page. 
 */
#define PAGE_SIZE       (0x1000U)

/**
 * @brief               The number of bits of a page.
 */
#define PAGE_BITS       12

/**
 * @brief               The page number of an address, shifted 10 bits
 *                      to the left.
 */
#define PAGE_ADDRESS(x) ((void *) (((uint32_t) x) & 0xFFFFF000))

/**
 * @brief               The page number of an address.
 */
#define PAGE_NUMBER(x)  (((address_t) x) >> PAGE_BITS)

/**
 * @brief               Size of some regions. 
 */
#define KERNEL_STACK_SIZE \
                        (4 * KIB)

/**
 * @brief               The kernel starts at 1 MiB. 
 */
#define KERNEL_BASE     (1 * MIB)

/**
 * @brief               The maximum memory amount that we support. 
 */
#define MAX_MEMORY      ((uint32_t) 2 * GIB)

/* Page directory/table flags. */
/**
 * @brief               Pages owned by the kernel.
 *
 * Supervisor-only, read-only (since we don't set WP bit, it isn't
 * really read-only for the kernel..), and global. 
 */
#define PAGE_KERNEL     PAGE_GLOBAL

/**
 * @brief               Pages owned by user processes.
 */
#define PAGE_USER       (PAGE_NON_PRIVILEGED | PAGE_WRITABLE | \
                         PAGE_WRITE_THROUGH)

/**
 * @brief               Is the page writable?
 */
#define PAGE_WRITABLE   BIT_VALUE (0)

/**
 * @brief               Can the page be accessed from nonprivileged (ring 3)
 *                      code?
 */
#define PAGE_NON_PRIVILEGED \
                        BIT_VALUE (1)

/**
 * @brief               Is write-through cache enabled for the page?
 */
#define PAGE_WRITE_THROUGH \
                        BIT_VALUE (2)

/**
 * @brief               Is caching completely disabled for this page?
 *
 * This flag is neccessary to use when mapping I/O devices.
 */
#define PAGE_CACHE_DISABLE \
                        BIT_VALUE (3)

/**
 * @brief               Is this a global page, shared between all page
 *                      directories?
 */
#define PAGE_GLOBAL     BIT_VALUE (4)

#endif /* (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__) */

#endif /* !__STORM_IA32_DEFINES_H__ */
