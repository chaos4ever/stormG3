/* $chaos: gdt.h,v 1.1 2002/05/25 20:09:39 per Exp $ */
/* Abstract: GDT definitions. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_GDT_H__
#define __STORM_IA32_GDT_H__

/* Defines. */
#define GDT(number,privilege)           (((number) << 3) + privilege)

/* Selectors. */
#define KERNEL_CODE_SELECTOR            (GDT (1, 0))
#define KERNEL_DATA_SELECTOR            (GDT (2, 0))
#define PROCESS_CODE_SELECTOR           (GDT (3, 3))
#define DATA_SELECTOR                   (GDT (4, 3))
#define TSS1_SELECTOR                   (GDT (5, 3))
#define TSS2_SELECTOR                   (GDT (6, 3))

#endif /* !__STORM_IA32_GDT_H__ */
