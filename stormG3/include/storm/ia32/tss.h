/* $chaos: dotfile.emacs,v 1.35 2002/10/04 18:41:41 per Exp $ */
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

#include <storm/ia32/flags.h>

/**
 * @brief               The CPU flags to use when setting up a new TSS.
 */
#define TSS_NEW_EFLAGS  (FLAG_INTERRUPT_ENABLE | FLAG_ADJUST | \
                         FLAG_PARITY | FLAG_SET)

/**
 * @brief               A TSS.
 */
typedef struct
{
    /**
     * @brief           CPU data. 
     */
    uint16_t            previous_task_link;
    uint16_t            u0;
    
    /**
     * @brief           Stack pointer for PL0 code (system calls). 
     */
    uint32_t            esp0;              

    /**
     * @brief           Stack segment for PL0 code (system calls).
     */
    uint16_t            ss0;

    uint16_t            u1;
    
    /**
     * @brief           Stack pointer for PL1 code (unused).
     */
    uint32_t            esp1;

    /**
     * @brief           Stack segment for PL1 code (unused).
     */
    uint16_t            ss1;
    uint16_t            u2;

    /**
     * @brief           Stack pointer for PL2 code (unused).
     */
    uint32_t            esp2;

    /**
     * @brief           Stack segment for PL2 code (unused).
     */
    uint16_t            ss2;
    uint16_t            u3;

    /**
     * @brief           CR3 (page directory) location.
     */
    uint32_t            cr3;
    
    /**
     * @brief           Instruction pointer.
     */
    uint32_t            eip;

    /**
     * @brief           Processor flags.
     */
    uint32_t            eflags;

    /**
     * @brief           General purpose register #1.
     */
    uint32_t            eax;

    /**
     * @brief           General purpose register #2.
     */
    uint32_t            ecx;

    /**
     * @brief           General purpose register #3.
     */
    uint32_t            edx;

    /**
     * @brief           General purpose register #4.
     */
    uint32_t            ebx;

    /**
     * @brief           Stack pointer. 
     */
    uint32_t            esp;

    /**
     * @brief           Base pointer.
     */
    uint32_t            ebp;

    /**
     * @brief           Source index (for MOVS)
     */
    uint32_t            esi;

    /**
     * @brief           Destination index (for MOVS)
     */
    uint32_t            edi;

    /**
     * @brief           ES segment selector.
     */
    uint16_t            es;
    uint16_t            u4;

    /**
     * @brief           CS segment selector.
     */
    uint16_t            cs;
    uint16_t            u5;

    /**
     * @brief           SS segment selector.
     */
    uint16_t            ss;
    uint16_t            u6;

    /**
     * @brief           DS segment selector.
     */
    uint16_t            ds;
    uint16_t            u7;

    /**
     * @brief           FS segment selector.
     */
    uint16_t            fs;
    uint16_t            u8;

    /**
     * @brief           GS segment selector.
     */
    uint16_t            gs;
    uint16_t            u9;
    
    /**
     * @brief           The selector in the GDT that refers to this
     *                  process LDT (Local Descriptor Table).
     *
     * We do not use this in stormG3.
     */
    uint16_t            ldt_selector;
    uint16_t            u10;
    uint16_t            t: 1;
    uint16_t            u11: 15;

    /**
     * @brief           Base address of I/O map, relative to the TSS 
     *                  location. 
     */
    uint16_t            iomap_base;
} tss_t PACKED;

#endif /* !__STORM_IA32_TSS_H__ */
