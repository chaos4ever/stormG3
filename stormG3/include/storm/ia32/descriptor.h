/* $chaos: descriptor.h,v 1.2 2002/08/11 17:16:49 per Exp $ */
/* Abstract: The descriptor structure. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_DESCRIPTOR_H__
#define __STORM_IA32_DESCRIPTOR_H__

#include <storm/types.h>

enum
{
    DESCRIPTOR_TYPE_TASK_GATE_32 = 5,
    DESCRIPTOR_TYPE_TSS = 9,
    DESCRIPTOR_TYPE_CALL_GATE = 12,
    DESCRIPTOR_TYPE_INTERRUPT_GATE_32 = 14,
    DESCRIPTOR_TYPE_TRAP_GATE_32 = 15,
};

typedef struct
{
    uint16_t limit_lo;                  /* Low 16 bits of segment limit. */
    uint16_t base_lo;                   /* Low 16 bits of base address. */
    uint8_t base_hi;                    /* Bits 16-23 of base address. */
    uint8_t type : 4;                   /* Segment type. */
    uint8_t descriptor_type : 1;        /* 0 = system, 1 = code or data. */
    uint8_t dpl : 2;                    /* Descriptor privilege level. */
    uint8_t segment_present : 1;        /* Zero if segment isn't used. */
    uint8_t limit_hi : 4;               /* High four bits of segment limit. */
    uint8_t : 1;                        /* Unused. */
    uint8_t zero : 1;                   /* Always zero! */
    uint8_t operation_size : 1;         /* 0 = 16-bit, 1 = 32-bit. */
    uint8_t granularity : 1;            /* If 1, segment limit is multiplied
                                          by 4096. */
    uint8_t base_hi2;                   /* Bits 24-31 of base address. */
} __attribute__ ((packed)) descriptor_t;

typedef struct
{
    uint16_t offset_lo;                 /* Low 16 bits of offset. */
    uint16_t segment_selector;
    uint8_t params : 5;                 /* Zero if not type == 12. */
    uint8_t zero : 3;                   /* Zero */
    uint8_t type : 5;                 
    uint8_t dpl : 2;                    /* Descriptor privilege level. */
    uint8_t present : 1;                /* If zero, this descriptor isn't
                                             used. */
    uint16_t offset_hi;                 /* High 16 bits of offset. */
} __attribute__ ((packed)) gate_descriptor_t;

#endif /* !__STORM_IA32_DESCRIPTOR_H__ */
