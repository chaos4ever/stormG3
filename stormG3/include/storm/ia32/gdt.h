/* $chaos: gdt.h,v 1.7 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                gdt.h 
 * @brief               GDT definitions.
 */

#ifndef __STORM_IA32_GDT_H__
#define __STORM_IA32_GDT_H__

#include <storm/ia32/descriptor.h>

/**
 * @brief               A GDT selector. 
 */
#define GDT(number,privilege)           (((number) << 3) + privilege)

/**
 * @brief               The location of the exceptions in the GDT. 
 */
#define GDT_BASE_EXCEPTIONS             (16)

/**
 * @brief               The number of max entries in the GDT. 
 */
#define GDT_ENTRIES                     (256)

/**
 * @brief               The size of the GDT.
 */
#define GDT_SIZE                        (GDT_ENTRIES * sizeof (descriptor_t))

/**
 * @brief               The kernel code selector.
 *
 * Used for kernel threads (currently only idle thread).
 */
#define KERNEL_CODE_SELECTOR            (GDT (1, 0))

/**
 * @brief               The kernel data selector.
 */
#define KERNEL_DATA_SELECTOR            (GDT (2, 0))

/**
 * @brief               The process code selector.
 */
#define PROCESS_CODE_SELECTOR           (GDT (3, 3))

/**
 * @brief               The process data selector.
 */
#define PROCESS_DATA_SELECTOR           (GDT (4, 3))

/**
 * @brief               The first TSS selector.
 *
 * We use two TSS selectors for task switching, which makes the GDT
 * very small which is good. Besides, it does not put a limit on the
 * number of running threads in the system which is *very* good.
 */
#define TSS1_SELECTOR                   (GDT (5, 3))

/**
 * @brief               The second TSS selector.
 */
#define TSS2_SELECTOR                   (GDT (6, 3))

/**
 * @brief               The GDT.
 */
extern descriptor_t gdt[];

#endif /* !__STORM_IA32_GDT_H__ */
