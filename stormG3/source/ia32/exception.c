/* $chaos: exception.c,v 1.6 2002/06/13 22:10:25 per Exp $ */
/* Abstract: Exception handling. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/ia32/cpu.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/exception.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/idt.h>

/* Exception handlers. */
exception_handler_t exception_handler[] =
{
    { &exception_divide_error_fault_lowlevel },
    { &exception_debug_trap_lowlevel },
    { &exception_nmi_lowlevel },
    { &exception_breakpoint_trap_lowlevel },
    { &exception_overflow_trap_lowlevel },
    { &exception_bound_range_exceeded_fault_lowlevel },
    { &exception_invalid_opcode_fault_lowlevel },
    { &exception_device_not_available_fault_lowlevel },
    { &exception_double_fault_lowlevel },
    { &exception_coprocessor_segment_overrun_abort_lowlevel },
    { &exception_invalid_tss_fault_lowlevel },
    { &exception_segment_not_present_fault_lowlevel },
    { &exception_stack_fault_lowlevel },
    { &exception_general_protection_fault_lowlevel },
    { &exception_page_fault_lowlevel },
    { &exception_dummy_lowlevel }, /* Should never occur. */
    { &exception_floating_point_error_fault_lowlevel },
    { &exception_alignment_check_fault_lowlevel },
    { &exception_machine_check_abort_lowlevel },
    { NULL }
};

/* Helper function to dump the registers on screen. */
static void dump_registers (cpu_register_t *registers)
{
    debug_print ("CS: %x EIP: %x EFLAGS: %x\n", registers->cs, registers->eip,
                 registers->eflags);
    debug_print ("DS:  %x ES:  %x FS:  %x GS:  %x\n",
                 registers->ds, registers->es, registers->fs, registers->gs);
    debug_print ("EAX: %x EBX: %x ECX: %x EDX: %x\n",
                 registers->eax, registers->ebx, registers->ecx,
                 registers->edx);
    debug_print ("ESI: %x EDI: %x EBP: %x ESP: %x\n",
                 registers->esi, registers->edi, registers->ebp,
                 registers->esp);
}

/* One function for each exception. */
void exception_divide_error_fault (cpu_register_t registers)
{
    debug_print ("Divide error fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_debug_trap (cpu_register_t registers)
{
    debug_print ("Debug trap.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_nmi (cpu_register_t registers)
{
    debug_print ("NMI.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_breakpoint_trap (cpu_register_t registers)
{
    debug_print ("Breakpoint trap.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_overflow_trap (cpu_register_t registers)
{
    debug_print ("Overflow trap.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_bound_range_exceeded_fault (cpu_register_t registers)
{
    debug_print ("Bound range exceeded fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_invalid_opcode_fault (cpu_register_t registers)
{
    debug_print ("Invalid opcode fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_device_not_available_fault (cpu_register_t registers)
{
    debug_print ("Device not available fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_double_fault (cpu_register_t registers)
{
    debug_print ("Double fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_coprocessor_segment_overrun_abort (cpu_register_t registers)
{
    debug_print ("Coprocessor segment overrun abort.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_invalid_tss_fault (cpu_register_t registers)
{
    debug_print ("Invalid TSS fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_segment_not_present_fault (cpu_register_t registers)
{
    debug_print ("Segment not present fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_stack_fault (cpu_register_t registers)
{
    debug_print ("Stack fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_general_protection_fault (cpu_register_t registers)
{
    debug_print ("General protection fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_page_fault (cpu_register_t registers)
{
    debug_print ("Page fault at %x, error code: %x.\n", cpu_get_cr2(), 
                 registers.error_code);
    dump_registers (&registers);
    //    while (TRUE);
}  

void exception_dummy (cpu_register_t registers)
{
    debug_print ("Dummy exception. This should never happen.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_floating_point_error_fault (cpu_register_t registers)
{
    debug_print ("Floating point error fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_alignment_check_fault (cpu_register_t registers)
{
    debug_print ("Exception alignment check fault.\n");
    dump_registers (&registers);
    while (TRUE);
}

void exception_machine_check_abort (cpu_register_t registers)
{
    debug_print ("Machine check abort.\n");
    dump_registers (&registers);
    while (TRUE);
}

/* Add an exception handler to the IDT. */
static void setup_handler (int number, void *handler)
{
    idt_setup_trap_gate (number, KERNEL_CODE_SELECTOR,
                         handler, 0);
}

/* Initialize exceptions. */
void exception_init () 
{
    /* Setup exception handlers for all exceptions. */
    int counter;
    for (counter = 0; exception_handler[counter].function != NULL; counter++)
    {
        setup_handler (counter, exception_handler[counter].function);
    }
}
