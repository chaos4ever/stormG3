/* $chaos: xemacs-script,v 1.6 2002/05/24 17:34:57 per Exp $ */
/* Abstract: Generic storm defines. */
/* Author: Per Lundberg <per@halleluja.nu> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_DEFINES_H__
#define __STORM_IA32_DEFINES_H__

#include <storm/defines.h>

/* The size of a physical page. */
#define PAGE_SIZE                       4096

/* Get the low or high 16 bits of a 32 bit integer
   variable. (Endian-specific) */
#define LOW_U16(x)                      ((x) & 0xFFFF)
#define HIGH_U16(x)                     ((x) >> 16)

/* Size of some reserved regions. */
#define GDT_SIZE                        (2 * KIB)
#define IDT_SIZE                        (2 * KIB)
#define KERNEL_STACK_SIZE               (4 * KIB)
#define MODULE_NAME_SIZE                (2 * KIB)
#define MEMORY_MAP_SIZE                 (2 * KIB)

/* Physical base addresses. */
#define GDT_BASE                        (4 * KIB)
#define IDT_BASE                        (GDT_BASE + GDT_BASE)
#define KERNEL_STACK_BASE               (IDT_BASE + IDT_BASE)
#define MODULE_NAME_BASE                (KERNEL_STACK_BASE + KERNEL_STACK_SIZE)
#define MEMORY_MAP_BASE                 (MODULE_NAME_BASE + MODULE_NAME_SIZE)

#endif /* !__STORM_IA32_DEFINES_H__ */
