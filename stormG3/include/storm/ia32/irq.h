/* $chaos: irq.h,v 1.11 2002/10/13 14:26:15 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                irq.h
 * @brief               IRQ handling.
 *
 * The low-level IRQ handlers (written in assembly and defined in
 * irq_handlers.S) are the interrupt handlers defined in the IDT. They
 * pass on control to the highlevel handler irq_handler, which in turn
 * passes on to interrupt handlers registered by kernel modules.
 */

#ifndef __STORM_IA32_IRQ_H__
#define __STORM_IA32_IRQ_H__

#include <storm/storm.h>
#include <storm/types.h>
#include <storm/ia32/process.h>
#include <storm/ia32/thread.h>

/**
 * @brief               The base addresses of 8259-1. 
 */
#define INTERRUPT_CONTROLLER_MASTER     0x20

/**
 * @brief               The base address of 8259-2. 
 */
#define INTERRUPT_CONTROLLER_SLAVE      0xA0

/**
 * @brief               The number of IRQ levels. 
 */
#define IRQ_LEVELS                      16

/**
 * @brief               The IRQ:s are mapped to interrupt 0x20 and 
 *                      upward. 
 */
#define BASE_IRQ                        0x20

/**
 * @brief               The IDT entry for IRQ level a.
 */
#define IRQ_IDT_ENTRY(a) \
                        (BASE_IRQ + a)

/**
 * @brief               A structure with information about an IRQ level. 
 */
typedef struct
{
    /**
     * @brief           Is this IRQ allocated? 
     */
    bool allocated;
    
    /**
     * @brief           A function pointer to the handler. 
     */
    irq_handler_t *handler;
    
    /**
     * @brief           A short description of the IRQ. 
     */
    char *description;

    /**
     * @brief           The number of currently unhandled interrupts. 
     */
    volatile unsigned int interrupts_pending;
  
    /**
     * @brief           The number of times this IRQ has been raised. 
     */
    unsigned long long occurred;

    /**
     * @brief           Are we currently handling this interrupt? 
     */
    volatile bool in_handler;
} irq_t;

/**
 * @brief               Initialize interrupt handling, and enable
 *                      interrupts. 
 */
extern void irq_init (void);

/**
 * @brief               Low-level IRQ 0 handler. 
 */
extern void irq0_handler (void);

/**
 * @brief               Low-level IRQ 1 handler. 
 */
extern void irq1_handler (void);

/**
 * @brief               Low-level IRQ 3 handler. 
 */
extern void irq3_handler (void);

/**
 * @brief               Low-level IRQ 4 handler. 
 */
extern void irq4_handler (void);

/**
 * @brief               Low-level IRQ 5 handler. 
 */
extern void irq5_handler (void);

/**
 * @brief               Low-level IRQ 6 handler. 
 */
extern void irq6_handler (void);

/**
 * @brief               Low-level IRQ 7 handler. 
 */
extern void irq7_handler (void);

/**
 * @brief               Low-level IRQ 8 handler. 
 */
extern void irq8_handler (void);

/**
 * @brief               Low-level IRQ 9 handler. 
 */
extern void irq9_handler (void);

/**
 * @brief               Low-level IRQ 10 handler. 
 */
extern void irq10_handler (void);

/**
 * @brief               Low-level IRQ 11 handler. 
 */
extern void irq11_handler (void);

/**
 * @brief               Low-level IRQ 12 handler. 
 */
extern void irq12_handler (void);

/**
 * @brief               Low-level IRQ 13 handler. 
 */
extern void irq13_handler (void);

/**
 * @brief               Low-level IRQ 14 handler. 
 */
extern void irq14_handler (void);

/**
 * @brief               Low-level IRQ 15 handler. 
 */
extern void irq15_handler (void);

/**
 * @brief               High-level interrupt handler. 
 * @param irq_number    The number of the IRQ to handle.
 */
extern void irq_handler (unsigned int irq_number);

#endif /* !__STORM_IA32_IRQ_H__ */
