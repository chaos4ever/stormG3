/* $chaos: exception_lowlevel.S,v 1.4 2002/06/14 22:47:27 per Exp $ */
/* Abstract: Low-level exception handlers. Push registers etc. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

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

#ifdef GDB
.globl catchException14
#endif /* GDB */
         
/* This (code duplication) doesn't look extremely nice, but it gives
   the best performance. The amount of instructions in an exception
   handler must be kept down. */
exception_divide_error_fault_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_divide_error_fault
	jmp save_registers

exception_debug_trap_lowlevel:
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_debug_trap
	jmp save_registers

exception_nmi_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_nmi_lowlevel
	jmp save_registers

exception_breakpoint_trap_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_breakpoint_trap
	jmp save_registers

exception_overflow_trap_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_overflow_trap
	jmp save_registers

exception_bound_range_exceeded_fault_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_bound_range_exceeded_fault
	jmp save_registers

exception_invalid_opcode_fault_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_invalid_opcode_fault
	jmp save_registers

exception_device_not_available_fault_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_device_not_available_fault
	jmp save_registers

exception_double_fault_lowlevel:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_double_fault
	jmp save_registers
		
exception_coprocessor_segment_overrun_abort_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_coprocessor_segment_overrun_abort
	jmp save_registers

exception_invalid_tss_fault_lowlevel:	
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_invalid_tss_fault
	jmp save_registers
	
exception_segment_not_present_fault_lowlevel:	
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_segment_not_present_fault
	jmp save_registers
	
exception_stack_fault_lowlevel:	
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_stack_fault
	jmp save_registers

exception_general_protection_fault_lowlevel:	
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_general_protection_fault
	jmp save_registers
	
exception_page_fault_lowlevel:
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_page_fault
	jmp save_registers

exception_dummy_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_dummy
	jmp save_registers
	
exception_floating_point_error_fault_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_floating_point_error_fault
	jmp save_registers
	
exception_alignment_check_fault_lowlevel:	
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_alignment_check_fault
	jmp save_registers

exception_machine_check_abort_lowlevel:
	pushl $-1 /* Error code. */
	pusha
	pushl %ds
	pushl %es
	pushl %fs
	pushl %gs
	pushl $exception_machine_check_abort
	jmp save_registers

/* Call the C exception handler, pop registers and return. */
save_registers:
	popl %eax
	call *%eax
#ifdef GDB
        /* Check the return value; if 1, call the GDB stub. Otherwise, just
           return as if the exception had never occured. */
        cmpl $1, %eax
        je gdb14
#endif /* GDB */
        
      	popl %eax /* GS */
	popl %eax /* FS */
	popl %eax /* ES */
	popl %eax /* DS */
	popa
	addl $0x4, %esp
        iret
        
#ifdef GDB
gdb14:
        /* Now, pass on control to GDB. */
      	popl %eax /* GS */
	popl %eax /* FS */
	popl %eax /* ES */
	popl %eax /* DS */
	popa
	addl $0x4, %esp

        jmp catchException14
#endif /* GDB */
