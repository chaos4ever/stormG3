/* $chaos: exception.c,v 1.4 2002/06/12 21:02:19 per Exp $ */
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

static inline void save_registers (void)
{
    asm volatile ("movl %%eax, registers + 0\n"
                  "movl %%ebx, registers + 4\n"
                  "movl %%ecx, registers + 8\n"
                  "movl %%edx, registers + 12\n"
                  "movl %%esi, registers + 16\n"
                  "movl %%edi, registers + 20\n"
                  :
                  :
                  :
                  "memory");
}

/* One function for each exception. */
static void exception_divide_error_fault (void)
{
    debug_print ("Divide error fault.\n");
    while (TRUE);
}

static void exception_debug_trap (void)
{
    debug_print ("Debug trap.\n");
    while (TRUE);
}

static void exception_nmi (void)
{
    debug_print ("NMI.\n");
    while (TRUE);
}

static void exception_breakpoint_trap (void)
{
    debug_print ("Breakpoint trap.\n");
    while (TRUE);
}

static void exception_overflow_trap (void)
{
    debug_print ("Overflow trap.\n");
    while (TRUE);
}

static void exception_bound_range_exceeded_fault (void)
{
    debug_print ("Bound range exceeded fault.\n");
    while (TRUE);
}

static void exception_invalid_opcode_fault (void)
{
    debug_print ("Invalid opcode fault.\n");
    while (TRUE);
}

static void exception_device_not_available_fault (void)
{
    debug_print ("Device not available fault.\n");
    while (TRUE);
}

static void exception_double_fault (void)
{
    debug_print ("Double fault.\n");
    while (TRUE);
}

static void exception_coprocessor_segment_overrun_abort (void)
{
    debug_print ("Coprocessor segment overrun abort.\n");
    while (TRUE);
}

static void exception_invalid_tss_fault (void)
{
    debug_print ("Invalid TSS fault.\n");
    while (TRUE);
}

static void exception_segment_not_present_fault (void)
{
    debug_print ("Segment not present fault.\n");
    while (TRUE);
}

static void exception_stack_fault (void)
{
    debug_print ("Stack fault.\n");
    while (TRUE);
}

static void exception_general_protection_fault (void)
{
    debug_print ("General protection fault.\n");
    while (TRUE);
}

void exception_page_fault (cpu_register_t *registers)
{
    debug_print ("Page fault at %x.\n", cpu_get_cr2());
    debug_print ("EAX: %x EBX: %x ECX: %x EDX: %x\n", registers->eax,
                 registers->ebx, registers->ecx, registers->edx);
    debug_print ("ESI: %x EDI: %x", registers->esi, 
                 registers->edi);
    while (TRUE);
}  

static void exception_floating_point_error_fault (void)
{
    debug_print ("Floating point error fault.\n");
    while (TRUE);
}

static void exception_alignment_check_fault (void)
{
    debug_print ("Exception alignment check fault.\n");
    while (TRUE);
}

static void exception_machine_check_abort (void)
{
    debug_print ("Machine check abort.\n");
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
