/* $chaos: defines.h,v 1.10 2002/06/13 06:15:30 per Exp $ */
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

/* Size of some reserved regions. These can take a maximum of 64k, 16
   full pages, because at that address the DMA buffers are put. */
#define KERNEL_STACK_SIZE               (4 * KIB)
#define GDT_SIZE                        (2 * KIB)
#define IDT_SIZE                        (2 * KIB)
#define MODULE_NAME_SIZE                (2 * KIB)
#define MEMORY_MAP_SIZE                 (2 * KIB)

/* Physical base addresses. */
#define KERNEL_STACK_BASE               (4 * KIB)
#define GDT_BASE                        (KERNEL_STACK_BASE + KERNEL_STACK_SIZE)
#define IDT_BASE                        (GDT_BASE + GDT_SIZE)
#define MODULE_NAME_BASE                (IDT_BASE + IDT_SIZE)
#define MEMORY_MAP_BASE                 (MODULE_NAME_BASE + MODULE_NAME_SIZE)

/* We reserve 3 8-bit DMA buffers (64 KiB each) and 3 16-bit DMA
   buffers (128 KiB each). */
#define DMA_BASE                        (64 * KIB)

/* The end of the fixed-address kernel memory regions. */
#define KERNEL_FIXED_END                (MEMORY_MAP_BASE + MEMORY_MAP_SIZE)

#endif /* !__STORM_IA32_DEFINES_H__ */
