/* $chaos: dotfile.emacs,v 1.35 2002/10/04 18:41:41 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */
/* Abstract: GDT functions. */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/ia32/gdt.h>
#include <storm/ia32/memory.h>

/* Create a TSS descriptor gate in the GDT. */
void gdt_setup_tss_descriptor (uint16_t selector, tss_t *address, int dpl,
                               int limit)
{
    descriptor_t descriptor;
    
    descriptor.limit_hi = 0;
    descriptor.limit_lo = limit;
    descriptor.granularity = 0;
    descriptor.base_lo = (address_t) address & 0xFFFF;
    descriptor.base_hi = ((address_t) address >> 16) & 0xFF;
    descriptor.base_hi2 = ((address_t) address >> 24) & 0xFF;
    descriptor.type = DESCRIPTOR_TYPE_TSS;
    descriptor.descriptor_type = 0;
    descriptor.dpl = dpl;
    descriptor.segment_present = 1;
    descriptor.zero = 0;
    descriptor.operation_size = 0;
    
    memory_copy (&gdt[selector], (void *) &descriptor, sizeof (descriptor_t));
}
