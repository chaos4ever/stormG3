/* $chaos: tss.h,v 1.2 2002/10/15 18:04:26 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                tss.h
 * @brief               A structure for holding an Intel TSS (Task
 *                      State Segment).
 *
 * TSS:es are used for doing task switching. All the register values
 * of a task is stored in the TSS.
 */

#ifndef __STORM_IA32_TSS_H__
#define __STORM_IA32_TSS_H__

#include <storm/ia32/cpu.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/types.h>

/**
 * @brief               The CPU flags to use when setting up a new TSS.
 */
#define TSS_NEW_EFLAGS  (CPU_FLAG_INTERRUPT_ENABLE | CPU_FLAG_ADJUST | \
                         CPU_FLAG_PARITY | CPU_FLAG_SET)

#endif /* !__STORM_IA32_TSS_H__ */
