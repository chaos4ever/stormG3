/* $chaos: defines.h,v 1.11 2002/06/15 11:00:23 per Exp $ */
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

/* We reserve 3 8-bit DMA buffers (64 KiB each) and 3 16-bit DMA
   buffers (128 KiB each). */
#define DMA_BASE                        (64 * KIB)

#endif /* !__STORM_IA32_DEFINES_H__ */
