/* $chaos: irq.h,v 1.7 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file irq.h
 * @brief IRQ handling.
 */

#ifndef __STORM_IA32_IRQ_H__
#define __STORM_IA32_IRQ_H__

#include <storm/storm.h>
#include <storm/types.h>
#include <storm/ia32/process.h>
#include <storm/ia32/thread.h>

/* Defines. */
/** @brief The base addresses of 8259-1. */
#define INTERRUPT_CONTROLLER_MASTER     0x20

/** @brief The base address of 8259-2. */
#define INTERRUPT_CONTROLLER_SLAVE      0xA0

/** @brief The number of IRQ levels. */
#define IRQ_LEVELS                      16

/* The IRQ:s are mapped to interrupt 0x20 and upward. */
#define BASE_IRQ                        0x20
#define IDT_ENTRY(a)                    (BASE_IRQ + a)

/** @brief A structure with information about an IRQ level. */
typedef struct
{
    /** Is this IRQ allocated? */
    bool allocated;
    
    /** A function pointer to the handler. */
    irq_handler_t *handler;
    
    /** A short description of the IRQ. */
    char *description;

    /** The number of currently unhandled interrupts. */
    volatile unsigned int interrupts_pending;
  
    /** The number of times this IRQ has been raised. */
    unsigned long long occurred;

    /** Are we currently handling this interrupt? */
    volatile bool in_handler;
} irq_t;

/** @brief Initialize interrupt handling, and enable interrupts. */
extern void irq_init (void);

/* Low-level interrupt handlers. */
extern void irq0_handler (void);
extern void irq1_handler (void);
extern void irq3_handler (void);
extern void irq4_handler (void);
extern void irq5_handler (void);
extern void irq6_handler (void);
extern void irq7_handler (void);
extern void irq8_handler (void);
extern void irq9_handler (void);
extern void irq10_handler (void);
extern void irq11_handler (void);
extern void irq12_handler (void);
extern void irq13_handler (void);
extern void irq14_handler (void);
extern void irq15_handler (void);

/** @brief High-level interrupt handler. */
extern void irq_handler (unsigned int irq_number);

#endif /* !__STORM_IA32_IRQ_H__ */
