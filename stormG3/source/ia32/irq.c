/* $chaos: irq.c,v 1.9 2002/10/23 21:09:23 per Exp $ */
/* Abstract: IRQ handling. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/return_value.h>
#include <storm/types.h>
#include <storm/ia32/bit.h>
#include <storm/ia32/cpu.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/dispatch.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/idt.h>
#include <storm/ia32/irq.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/port.h>
#include <storm/ia32/process.h>
#include <storm/ia32/string.h>
#include <storm/ia32/thread.h>

static irq_t irq[IRQ_LEVELS];

/* Just a short delay, to wait for the IRQ controller. */
static void delay (void)
{
    asm ("nop\n"
         "nop\n"
         "nop\n"
         "jmp 1f\n"
         "1:");
}

/* Enable the given interrupt. */
static void irq_enable (unsigned int irq_number)
{
    uint8_t mask;

    /* Check which interrupt controller to use. */
    if (irq_number < 8)
    {
        mask = (port_uint8_in (INTERRUPT_CONTROLLER_MASTER + 1) &
                ~BIT_VALUE (irq_number));
        port_uint8_out (INTERRUPT_CONTROLLER_MASTER + 1, mask);
    }
    else
    {
        mask = (port_uint8_in (INTERRUPT_CONTROLLER_SLAVE + 1) &
                ~BIT_VALUE (irq_number - 8));
        port_uint8_out (INTERRUPT_CONTROLLER_SLAVE + 1, mask);
    }
}

/* Remap all IRQ:s to 0x20-0x2F. */
static void irq_remap (void)
{
    /* Send initialisation sequence to 8259A-1 and 8259A-2. */
    port_uint8_out (INTERRUPT_CONTROLLER_MASTER, 0x11);
    delay ();
    port_uint8_out (INTERRUPT_CONTROLLER_SLAVE, 0x11);
    delay ();
    
    /* Start of hardware int's (0x20). */
    port_uint8_out (INTERRUPT_CONTROLLER_MASTER + 1, BASE_IRQ);
    delay ();
    
    /* Start of hardware int's 2 (0x28). */
    port_uint8_out (INTERRUPT_CONTROLLER_SLAVE + 1, BASE_IRQ + 8);
    delay ();

    /* 8259-1 is master. */
    port_uint8_out (INTERRUPT_CONTROLLER_MASTER + 1, 0x04);
    delay ();

    /* 8259-2 is slave. */
    port_uint8_out (INTERRUPT_CONTROLLER_SLAVE + 1, 0x02);
    delay ();

    /* 8086 mode for both. */
    port_uint8_out (INTERRUPT_CONTROLLER_MASTER + 1, 0x01);
    delay ();
    port_uint8_out (INTERRUPT_CONTROLLER_SLAVE + 1, 0x01);
    delay ();
}

/* Initialize IRQ handling. */
void irq_init ()
{
    memory_set_uint8 ((uint8_t *) irq, 0, sizeof (irq_t) * IRQ_LEVELS);

    /* Remap the IRQs to 20-2F, so they won't overlap the exceptions. */
    irq_remap ();

    /* Set up a handler for the task switcher. */
    idt_setup_interrupt_gate (IRQ_IDT_ENTRY(0), KERNEL_CODE_SELECTOR,
                              irq0_handler, 0);
    
    idt_setup_trap_gate (IRQ_IDT_ENTRY(1), KERNEL_CODE_SELECTOR,
                         irq1_handler, 0);
    
    /* IRQ 2 is used to connect the two interrupt controllers and can
       not be used as an ordinary IRQ. */
    idt_setup_trap_gate (IRQ_IDT_ENTRY(3), KERNEL_CODE_SELECTOR,
                         irq3_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(4), KERNEL_CODE_SELECTOR,
                         irq4_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(5), KERNEL_CODE_SELECTOR,
                         irq5_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(6), KERNEL_CODE_SELECTOR,
                         irq6_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(7), KERNEL_CODE_SELECTOR,
                         irq7_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(8), KERNEL_CODE_SELECTOR,
                         irq8_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(9), KERNEL_CODE_SELECTOR,
                         irq9_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(10), KERNEL_CODE_SELECTOR,
                         irq10_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(11), KERNEL_CODE_SELECTOR,
                         irq11_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(12), KERNEL_CODE_SELECTOR,
                         irq12_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(13), KERNEL_CODE_SELECTOR,
                         irq13_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(14), KERNEL_CODE_SELECTOR,
                         irq14_handler, 0);
    idt_setup_trap_gate (IRQ_IDT_ENTRY(15), KERNEL_CODE_SELECTOR,
                         irq15_handler, 0);
    
    /* Disable all IRQs. */
    port_uint8_out (INTERRUPT_CONTROLLER_MASTER + 1, 0xFF);
    port_uint8_out (INTERRUPT_CONTROLLER_SLAVE + 1, 0xFF);
    
    /* Allocate IRQ 0 and 2 for the system. */
    irq[0].allocated = TRUE;
    irq[0].handler = NULL;
    irq[0].description = (char *) "System timer";
    irq_enable (0);

    irq[2].allocated = TRUE;
    irq[2].handler = NULL;
    irq[2].description = (char *) "Cascade IRQ";
    irq_enable (2);

    /* Enable interrupts. */
    cpu_interrupts_enable ();
}

/* ACK the given interrupt. */
static inline void ack_interrupt (unsigned int irq_number)
{
    /* If this is a low interrupt, ACK:ing the low PIC is enough;
       otherwise, we'll have to do the other one too. */
    if (irq_number < 8)
    {
        port_uint8_out (INTERRUPT_CONTROLLER_MASTER, 0x20);
    }
    else
    {
        /* The order is important here. */
        port_uint8_out (INTERRUPT_CONTROLLER_SLAVE, 0x20);
        port_uint8_out (INTERRUPT_CONTROLLER_MASTER, 0x20);
    }
}

/* This function handles all interrupts except for the timer
   interrupt. */
void irq_handler (unsigned int irq_number)
{
    irq[irq_number].interrupts_pending++;

    if (irq[irq_number].in_handler)
    {
        ack_interrupt (irq_number);
        return;
    }

    irq[irq_number].in_handler = TRUE;
    irq[irq_number].occurred++;
    
    if (!irq[irq_number].allocated)
    {
        debug_print ("Unexpected interrupt %u occured!", irq_number);
    }
    else
    {
        /* Call the IRQ handler for this device. */
        if (irq[irq_number].handler != NULL)
        {
            do {
                irq[irq_number].handler (irq_number);
                // FIXME: These two need to be one atomic operation.
                irq[irq_number].interrupts_pending--;
            } while (irq[irq_number].interrupts_pending > 0);
        }
    }

    ack_interrupt (irq_number);
    
    irq[irq_number].in_handler = FALSE;
}

/* Register an IRQ for use by a module. */
return_t irq_register (unsigned int irq_number, char *description,
                       irq_handler_t *function)
{
    return_t return_value;

    /* Make sure the input data is pure. */
    if (irq_number >= IRQ_LEVELS)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }
    
    //mutex_kernel_wait (&tss_tree_mutex);

    /* Make sure the IRQ level is free. */
    if (irq[irq_number].allocated)
    {
        //mutex_kernel_signal (&tss_tree_mutex);
        return STORM_RETURN_BUSY;
    }
    
    /* Update the information in the IRQ structure. */
    return_value = memory_global_allocate ((void **) &irq[irq_number].description,
                                          string_length (description) + 1);
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    string_copy (irq[irq_number].description, description);
    
    irq[irq_number].allocated = TRUE;
    irq[irq_number].interrupts_pending = 0;
    irq[irq_number].handler = function;
    irq_enable (irq_number);

    //mutex_kernel_signal (&tss_tree_mutex);
    return STORM_RETURN_SUCCESS;
}
