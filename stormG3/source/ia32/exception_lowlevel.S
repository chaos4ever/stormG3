/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Low-level exception handlers. Push registers etc. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

.globl exception_divide_error_fault_lowlevel
.globl exception_debug_trap_lowlevel
.globl exception_nmi_lowlevel
.globl exception_breakpoint_trap_lowlevel
.globl exception_overflow_trap_lowlevel
.globl exception_bound_range_exceeded_fault_lowlevel
.globl exception_invalid_opcode_fault_lowlevel
.globl exception_device_not_available_fault_lowlevel
.globl exception_double_fault_lowlevel
.globl exception_coprocessor_segment_overrun_abort_lowlevel
.globl exception_invalid_tss_fault_lowlevel
.globl exception_segment_not_present_fault_lowlevel
.globl exception_stack_fault_lowlevel
.globl exception_general_protection_fault_lowlevel
.globl exception_page_fault_lowlevel
.globl exception_dummy_lowlevel
.globl exception_floating_point_error_fault_lowlevel
.globl exception_alignment_check_fault_lowlevel
.globl exception_machine_check_abort_lowlevel

exception_divide_error_fault_lowlevel:	
exception_debug_trap_lowlevel:	
exception_nmi_lowlevel:	
exception_breakpoint_trap_lowlevel:	
exception_overflow_trap_lowlevel:	
exception_bound_range_exceeded_fault_lowlevel:	
exception_invalid_opcode_fault_lowlevel:	
exception_device_not_available_fault_lowlevel:	
exception_double_fault_lowlevel:	
exception_coprocessor_segment_overrun_abort_lowlevel:	
exception_invalid_tss_fault_lowlevel:	
exception_segment_not_present_fault_lowlevel:	
exception_stack_fault_lowlevel:	
exception_general_protection_fault_lowlevel:	
	ret
	
exception_page_fault_lowlevel:
	pushl $exception_page_fault
	jmp save_registers

exception_dummy_lowlevel:	
exception_floating_point_error_fault_lowlevel:	
exception_alignment_check_fault_lowlevel:	
exception_machine_check_abort_lowlevel:
	ret
	
save_registers:
	addl 4, %esp
	ret
