/* $chaos: defines.h,v 1.14 2002/06/17 20:57:30 per Exp $ */
/* Abstract: Generic storm defines. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_DEFINES_H__
#define __STORM_IA32_DEFINES_H__

#include <storm/defines.h>
#include <storm/types.h>

/* The size of a physical page. */
#define PAGE_SIZE                       0x1000

/* The page number of an address, shifted 10 bits to the left. */
#define PAGE_ADDRESS(x)                 ((void *) (((uint32_t) x) & 0xFFFFF000))

/* Size of some regions. */
#define KERNEL_STACK_SIZE               (4 * KIB)

/* The kernel starts at 1 MiB. */
#define KERNEL_BASE                     (1 * MIB)

/* The maximum memory amount that we support. */
#define MAX_MEMORY                      ((uint32_t) 2 * GIB)

#endif /* !__STORM_IA32_DEFINES_H__ */
