/* $chaos: system_call.c,v 1.2 2002/10/24 22:13:38 per Exp $ */
/* Abstract: */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <storm/ia32/cpu.h>
#include <storm/ia32/dispatch.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/idt.h>
#include <storm/ia32/system_call.h>

/* Set up the system call handler in the IDT. */
void system_call_init (void)
{
    idt_setup_interrupt_gate (SYSTEM_CALL_IDT_ENTRY,
                              KERNEL_CODE_SELECTOR, system_call_lowlevel, 3);
}

/* The high-level system call handler, called from the low-level function. */
void system_call (uint32_t *stack)
{
    /* stack[0] is the number of arguments, stack[1..n] is the
       arguments. */
    bool result;
    return_t return_value = capability_has (0, current_process, "kernel",
                                            "debug_print", &result);
    
    if (return_value == STORM_RETURN_SUCCESS &&
        result)
    {
        //        address_t esp = cpu_get_esp ();
        //        debug_memory_dump ((uint32_t *) esp, 17);
        debug_print ("We have a system call! %x", stack[0]);
        debug_print ("This is the string: %s\n", stack[1]);
    }
    else
    {
        debug_print ("You don't have the permission to do this.");
    }
}
