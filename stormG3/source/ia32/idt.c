/* $chaos: idt.c,v 1.3 2002/06/15 14:35:04 per Exp $ */
/* Abstract: IDT management. */
/* Authors: Per Lundberg <per@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */

#include <storm/ia32/debug.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/descriptor.h>
#include <storm/ia32/idt.h>
#include <storm/ia32/memory.h>

descriptor_t idt[IDT_ENTRIES] __attribute__ ((section (".idt")));

/* Create a trap gate. Make sure to have interrupts disabled while
   running this one; a task switch in the middle could case very bad
   effects. */
void idt_setup_trap_gate (unsigned int number, unsigned int selector, 
                          void *address, unsigned int privilege_level)
{
    gate_descriptor_t *gate_descriptor = (gate_descriptor_t *) &idt[number];
    
    // FIXME: Use macros.
    gate_descriptor->offset_lo = (uint32_t) address & 0xFFFF;
    gate_descriptor->offset_hi = ((uint32_t) address >> 16) & 0xFFFF;
    gate_descriptor->segment_selector = selector;
    gate_descriptor->params = 0;
    gate_descriptor->zero = 0;
    gate_descriptor->dpl = privilege_level;
    gate_descriptor->present = 1;
    gate_descriptor->segment_selector = selector;
    gate_descriptor->params = 0;
    gate_descriptor->zero = 0;
    gate_descriptor->dpl = privilege_level;
    gate_descriptor->present = 1;
    gate_descriptor->type = DESCRIPTOR_TYPE_TRAP_GATE_32;
}

/* Create an interrupt gate. Make sure to have interrupts disabled
   while running this one; a task switch in the middle could case very
   bad effects. */
void idt_setup_interrupt_gate (unsigned int number, unsigned int selector, 
                               void *address, unsigned int privilege_level)
{
    gate_descriptor_t *gate_descriptor = (gate_descriptor_t *) &idt[number];
    
    // FIXME: Use macros.
    gate_descriptor->offset_lo = (uint32_t) address & 0xFFFF;
    gate_descriptor->offset_hi = ((uint32_t) address >> 16) & 0xFFFF;
    gate_descriptor->segment_selector = selector;
    gate_descriptor->params = 0;
    gate_descriptor->zero = 0;
    gate_descriptor->dpl = privilege_level;
    gate_descriptor->present = 1;
    gate_descriptor->segment_selector = selector;
    gate_descriptor->params = 0;
    gate_descriptor->zero = 0;
    gate_descriptor->dpl = privilege_level;
    gate_descriptor->present = 1;
    gate_descriptor->type = DESCRIPTOR_TYPE_INTERRUPT_GATE_32;
}
