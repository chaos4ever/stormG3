/* $chaos: cpu.h,v 1.7 2002/06/13 20:07:38 per Exp $ */
/* Abstract: CPU defines and functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_CPU_H__
#define __STORM_IA32_CPU_H__

#include <storm/types.h>
#include <storm/ia32/bit.h>
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
                  : "=r" (return_value) 
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
		: "=r" (return_value)
		:);

  return return_value;
}

/* Function prototypes. */
extern void cpu_init (void);

/* Type definitions. */
/* What we get out of CPUID. */
typedef struct
{
    /* Feature flags. */
    uint32_t fpu:       1;
    uint32_t vme:       1;
    uint32_t de:        1;
    uint32_t pse:       1;
    uint32_t tsc:       1;
    uint32_t msr:       1;
    uint32_t pae:       1;
    uint32_t mce:       1;
    uint32_t cx8:       1;
    uint32_t apic:      1;
    uint32_t ff_res0:   1;
    uint32_t sep:       1;
    uint32_t mtrr:      1;
    uint32_t pge:       1;
    uint32_t mca:       1;
    uint32_t cmov:      1;
    uint32_t pat:       1;
    uint32_t pse_36:    1;
    uint32_t ff_res1:   5;
    uint32_t mmx:       1;
    uint32_t fxsr:      1;
    uint32_t sse:       1;
    uint32_t ff_res2:   5;
    uint32_t amd_3dnow: 1;
} __attribute__ ((packed)) cpuid_flags_t;

/* Information about a CPU. */
typedef struct
{
  uint32_t cpuid;
  
  const char *name;
  
  /* Phony variable. Since C is so stupid it won't let me have union
     elements accessed the same way as the rest of the structure, we
     have to hack it a little.. */
  uint32_t signature[0];

  /* CPU signature. */
  uint32_t stepping: 4;
  uint32_t model:    4;
  uint32_t family:   4;
  uint32_t type:     2;
  uint32_t s_res0:   18;

  union
  {
    uint32_t real_flags;
    cpuid_flags_t flags;
  } flags;
 
  /* CPU configuration. */
  uint32_t configuration;
} __attribute__ ((packed)) cpu_info_t;

/* The IA32 registers. In convenient order. */
typedef struct
{
    /* These ones are pushed manually. */
    uint32_t ds, es, fs, gs;

    /* These are gently stored by a pusha. */
    uint32_t edi, esi, ebp, esp;
    uint32_t ebx, edx, ecx, eax;
} cpu_register_t;

/* External variables. */
extern cpu_info_t cpu_info;

/* CPUID functions. */
enum
{
    CPUID_GET_CPU_VENDOR,
    CPUID_GET_CPU_INFO,
};

/* CR0 bits. */
/* Paging enabled. */
#define CPU_CR0_PG (BIT_VALUE (31))

/* Protected mode flag. */
#define CPU_CR0_PE (BIT_VALUE (0))

/* Extension type. */
#define CPU_CR0_ET (BIT_VALUE (4))

/* Write protect (486+). */
#define CPU_CR0_WP (BIT_VALUE (16))

/* Flags in the EFLAGS register. See the Intel documentation for more
   information about what those does. */
enum
{
    CPU_FLAG_CARRY = (BIT_VALUE (0)),
    CPU_FLAG_SET = (BIT_VALUE (1)),
    CPU_FLAG_PARITY = (BIT_VALUE (2)),
    CPU_FLAG_ADJUST = (BIT_VALUE (4)),
    CPU_FLAG_ZERO = (BIT_VALUE (6)),
    CPU_FLAG_SIGN = (BIT_VALUE (7)),
    CPU_FLAG_TRAP = (BIT_VALUE (8)),
    CPU_FLAG_INTERRUPT_ENABLE = (BIT_VALUE (9)),
    CPU_FLAG_DIRECTION = (BIT_VALUE (10)),
    CPU_FLAG_OVERFLOW = (BIT_VALUE (11)),
    CPU_FLAG_IOPL_LOW = (BIT_VALUE (12)),
    CPU_FLAG_IOPL_HIGH = (BIT_VALUE (13)),
    CPU_FLAG_NESTED_TASK = (BIT_VALUE (14)),
    CPU_FLAG_RESUME_TASK = (BIT_VALUE (16)),
    CPU_FLAG_V8086_MODE = (BIT_VALUE (17)),
    CPU_FLAG_ALIGNMENT_CHECK = (BIT_VALUE (18)),
    CPU_FLAG_VIRTUAL_INTERRUPT = (BIT_VALUE (19)),
    CPU_FLAG_VIRTUAL_INTERRUPT_PENDING = (BIT_VALUE (20)),
    CPU_FLAG_ID = (BIT_VALUE (21))
};

#endif /* !__STORM_IA32_CPU_H__ */
