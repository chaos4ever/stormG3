/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Exception handling. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/ia32/exception.h>

#if FALSE
/* Initialise exceptions. */
static void setup_handler (u32 number, void *exception_handler)
{
    /* Add it to the IDT. */
    //    idt_setup_call_gate (number, GDT (GDT_BASE_EXCEPTIONS + number, 0), 0);
}
#endif

void exception_init () 
{
#if FALSE
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
    setup_handler (15, exception_klotis_fault);
    setup_handler (16, exception_floating_point_error_fault);
    setup_handler (17, exception_alignment_check_fault);
    setup_handler (18, exception_machine_check_abort);
#endif
}
