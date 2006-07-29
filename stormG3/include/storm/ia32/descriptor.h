/* $chaos: descriptor.h,v 1.5 2002/10/10 21:42:55 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** @file descriptor.h
    @brief The descriptor structure. */

#ifndef __STORM_IA32_DESCRIPTOR_H__
#define __STORM_IA32_DESCRIPTOR_H__

#include <storm/defines.h>
#include <storm/ia32/types.h>

/**
 * @brief               Descriptor types.
 */
enum descriptor_type
{
    /**
     * @brief           A 32-bit task gate.
     */
    DESCRIPTOR_TYPE_TASK_GATE_32 = 5,

    /**
     * @brief           A TSS gate.
     */
    DESCRIPTOR_TYPE_TSS = 9,

    /**
     * @brief           A call gate.
     */
    DESCRIPTOR_TYPE_CALL_GATE = 12,

    /**
     * @brief           A 32-bit interrupt gate.
     */
    DESCRIPTOR_TYPE_INTERRUPT_GATE_32 = 14,

    /**
     * @brief           A 32-bit trap gate. 
     */
    DESCRIPTOR_TYPE_TRAP_GATE_32 = 15,
};

/** 
 * @brief               A descriptor. 
 */
typedef struct PACKED
{
    /**
     * @brief           Low 16 bits of segment limit. 
     */
    uint16_t limit_lo;

    /**
     * @brief           Low 16 bits of base address. 
     */
    uint16_t base_lo;

    /**
     * @brief           Bits 16-23 of base address. 
     */
    uint8_t base_hi;

    /**
     * @brief           Segment type. 
     */
    uint8_t type : 4;

    /**
     * @brief           0 = system, 1 = code or data. 
     */
    uint8_t descriptor_type : 1;

    /**
     * @brief           Descriptor privilege level. 
     */
    uint8_t dpl : 2;

    /**
     * @brief           Zero if segment isn't used. 
     */
    uint8_t segment_present : 1;

    /**
     * @brief           High four bits of segment limit. 
     */
    uint8_t limit_hi : 4;

    /* Unused. */
    uint8_t : 1;

    /**
     * @brief           Always zero! 
     */
    uint8_t zero : 1;

    /**
     * @brief           0 = 16-bit, 1 = 32-bit. 
     */
    uint8_t operation_size : 1;

    /**
     * @brief           If 1, segment limit is multiplied by 4096. 
     */
    uint8_t granularity : 1;

    /**
     * @brief           Bits 24-31 of base address. 
     */
    uint8_t base_hi2;
} descriptor_t;

/**
 * @brief               A gate descriptor. 
 */
typedef struct PACKED
{
    /**
     * @brief           Low 16 bits of offset. 
     */
    uint16_t offset_lo;
    uint16_t segment_selector;

    /**
     * @brief           Zero if not type == 12. 
     */
    uint8_t params : 5;

    /*
     * @brief           Zero 
     */
    uint8_t zero : 3;
    uint8_t type : 5;                 

    /**
     * @brief           Descriptor privilege level. 
     */
    uint8_t dpl : 2;

    /**
     * @brief           If zero, this descriptor isn't used. 
     */
    uint8_t present : 1;

    /**
     * @brief           High 16 bits of offset. 
     */
    uint16_t offset_hi;
} gate_descriptor_t;

#endif /* !__STORM_IA32_DESCRIPTOR_H__ */
