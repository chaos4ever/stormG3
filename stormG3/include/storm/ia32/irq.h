/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: IRQ handling. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_IRQ_H__
#define __STORM_IA32_IRQ_H__

#include <storm/types.h>
#include <storm/ia32/process.h>
#include <storm/ia32/thread.h>

/* Defines. */
/* The base addresses of 8259-1 and 8259-2. */

#define INTERRUPT_CONTROLLER_MASTER     0x20
#define INTERRUPT_CONTROLLER_SLAVE      0xA0

/* The number of IRQ levels. */
#define IRQ_LEVELS                      16

/* The IRQ:s are mapped to interrupt 0x20 and upward. */
#define BASE_IRQ                        0x20
#define IDT_ENTRY(a)                    (BASE_IRQ + a)

/* Type definitions. */
typedef struct
{
    bool allocated;
    
    /* A function pointer to the handler. */
    //    (void *handler)(unsigned int irq_level);
  
    /* A short description of the IRQ. */
    char *description;

    /* The number of currently unhandled interrupts. */
    unsigned int interrupts_pending;
  
    /* The number of times this IRQ has been raised. */
    unsigned long long occurred;
    volatile bool in_handler;
} irq_t;

/* Initialize interrupt handling, and enable interrupts. */
extern void irq_init (void);

/* Low-level interrupt handlers. */
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

/* High-level interrupt handler. */
extern void irq_handler (unsigned int irq_number);

#endif /* !__STORM_IA32_IRQ_H__ */
