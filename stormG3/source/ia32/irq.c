/* $chaos: irq.c,v 1.2 2002/06/15 11:29:53 per Exp $ */
/* Abstract: IRQ handling. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

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
#include <storm/ia32/port.h>
#include <storm/ia32/process.h>
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
    idt_setup_interrupt_gate (IDT_ENTRY(0), KERNEL_CODE_SELECTOR,
                              dispatch_task_switcher, 0);
    
    idt_setup_interrupt_gate (IDT_ENTRY(1), KERNEL_CODE_SELECTOR,
                              irq1_handler, 0);
    
    /* IRQ 2 is used to connect the two interrupt controllers and can
       not be used as an ordinary IRQ. */
    idt_setup_interrupt_gate (IDT_ENTRY(3), KERNEL_CODE_SELECTOR,
                              irq3_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(4), KERNEL_CODE_SELECTOR,
                              irq4_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(5), KERNEL_CODE_SELECTOR,
                              irq5_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(6), KERNEL_CODE_SELECTOR,
                              irq6_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(7), KERNEL_CODE_SELECTOR,
                              irq7_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(8), KERNEL_CODE_SELECTOR,
                              irq8_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(9), KERNEL_CODE_SELECTOR,
                              irq9_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(10), KERNEL_CODE_SELECTOR,
                              irq10_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(11), KERNEL_CODE_SELECTOR,
                              irq11_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(12), KERNEL_CODE_SELECTOR,
                              irq12_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(13), KERNEL_CODE_SELECTOR,
                              irq13_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(14), KERNEL_CODE_SELECTOR,
                              irq14_handler, 0);
    idt_setup_interrupt_gate (IDT_ENTRY(15), KERNEL_CODE_SELECTOR,
                              irq15_handler, 0);
    
    /* Disable all IRQs. */
    port_uint8_out (INTERRUPT_CONTROLLER_MASTER + 1, 0xFF);
    port_uint8_out (INTERRUPT_CONTROLLER_SLAVE + 1, 0xFF);
    
    /* Allocate IRQ 0 and 2 for the system. */
    irq[0].allocated = TRUE;
    irq[0].handler = NULL;
    irq[0].description = "System timer";
    irq_enable (0);

    irq[2].allocated = TRUE;
    irq[2].handler = NULL;
    irq[2].description = "Cascade IRQ";
    irq_enable (2);

    /* Enable interrupts. */
    cpu_interrupts_enable ();
}

/* This function handles all interrupts except for the timer
   interrupt. */
void irq_handler (unsigned int irq_number)
{
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
          irq[irq_number].handler (irq_number);
      }
  }

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

  irq[irq_number].in_handler = FALSE;
}
