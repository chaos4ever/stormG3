/* $chaos: exception.c,v 1.2 2002/06/11 21:26:50 per Exp $ */
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

static void exception_page_fault (void)
{
    debug_print ("Page fault at %x.\n", cpu_get_cr2());
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
static void setup_handler (int number, void *exception_handler)
{
    idt_setup_trap_gate (number, KERNEL_CODE_SELECTOR,
                         exception_handler, 0);
}

/* Initialize exceptions. */
void exception_init () 
{
    /* Setup exception handlers for all exceptions. */
    setup_handler (0, exception_divide_error_fault);
    setup_handler (1, exception_debug_trap);
    setup_handler (2, exception_nmi);
    setup_handler (3, exception_breakpoint_trap);
    setup_handler (4, exception_overflow_trap);
    setup_handler (5, exception_bound_range_exceeded_fault);
    setup_handler (6, exception_invalid_opcode_fault);
    setup_handler (7, exception_device_not_available_fault);
    setup_handler (8, exception_double_fault);
    setup_handler (9, exception_coprocessor_segment_overrun_abort);
    setup_handler (10, exception_invalid_tss_fault);
    setup_handler (11, exception_segment_not_present_fault);
    setup_handler (12, exception_stack_fault);
    setup_handler (13, exception_general_protection_fault);
    setup_handler (14, exception_page_fault);
    setup_handler (16, exception_floating_point_error_fault);
    setup_handler (17, exception_alignment_check_fault);
    setup_handler (18, exception_machine_check_abort);
}
