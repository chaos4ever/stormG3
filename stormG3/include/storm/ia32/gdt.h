/* $chaos: gdt.h,v 1.6 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file gdt.h 
 * @brief GDT definitions.
 */

#ifndef __STORM_IA32_GDT_H__
#define __STORM_IA32_GDT_H__

#include <storm/ia32/descriptor.h>

/* Defines. */
/* A GDT selector. */
#define GDT(number,privilege)           (((number) << 3) + privilege)

/* The location of the exceptions in the GDT. */
#define GDT_BASE_EXCEPTIONS             (16)

/* The number of max entries in the GDT. */
#define GDT_ENTRIES                     (256)

#define GDT_SIZE                        (GDT_ENTRIES * sizeof (descriptor_t))

/* Selectors. */
#define KERNEL_CODE_SELECTOR            (GDT (1, 0))
#define KERNEL_DATA_SELECTOR            (GDT (2, 0))
#define PROCESS_CODE_SELECTOR           (GDT (3, 3))
#define PROCESS_DATA_SELECTOR           (GDT (4, 3))
#define TSS1_SELECTOR                   (GDT (5, 3))
#define TSS2_SELECTOR                   (GDT (6, 3))

/* External variables. */
extern descriptor_t gdt[];

#endif /* !__STORM_IA32_GDT_H__ */
