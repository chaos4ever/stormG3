/* $chaos: cpu.h,v 1.3 2002/06/12 19:29:15 per Exp $ */
/* Abstract: CPU defines and functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_CPU_H__
#define __STORM_IA32_CPU_H__

#include <storm/types.h>
#include <storm/ia32/defines.h>

/* Inline functions. */
static inline void cpu_set_cr0 (uint32_t new_cr0)
{
    asm volatile ("movl %0, %%cr0"
                  :
                  : "r" (new_cr0));
}

static inline uint32_t cpu_get_cr2 (void)
{			   
    uint32_t return_value;
    asm volatile ("movl %%cr2, %0"
                  : "=a" (return_value) 
                  :);
    return return_value;
}

static inline void cpu_set_cr3 (uint32_t new_cr3)
{
    asm volatile ("movl %0, %%cr3"
                  :
                  : "r" (new_cr3));
}

static inline uint32_t cpu_get_esp (void)
{
  uint32_t return_value;

  asm volatile ("movl %%esp, %0"
		: "=a" (return_value)
		:);

  return return_value;
}

/* CR0 bits. */
/* Paging enabled. */
#define CPU_CR0_PG (BIT_VALUE (31))

/* Protected mode flag. */
#define CPU_CR0_PE (BIT_VALUE (0))

/* Extension type. */
#define CPU_CR0_ET (BIT_VALUE (4))

/* Write protect (486+). */
#define CPU_CR0_WP (BIT_VALUE (16))

#endif /* !__STORM_IA32_CPU_H__ */
