/* $chaos: exception.h,v 1.6 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file exception.h
 * @brief Exception handling. 
 */

#ifndef __STORM_IA32_EXCEPTION_H__
#define __STORM_IA32_EXCEPTION_H__

#include <storm/ia32/cpu.h>

/* Types. */
/** 
 * @brief               An exception handler. 
 */
typedef struct
{
    void *function;
} exception_handler_t;

/**
 * @brief               Initialize exception handling. 
 */
extern void exception_init (void);

// FIXME: Define the exception names.
/**
 * @brief               Page fault exception. 
 */
#define EXCEPTION_PAGE_FAULT \
                        (14)

/* Exception handlers prototypes. Low-level first: */
extern void exception_divide_error_fault_lowlevel (void);
extern void exception_debug_trap_lowlevel (void);
extern void exception_nmi_lowlevel (void);
extern void exception_breakpoint_trap_lowlevel (void);
extern void exception_overflow_trap_lowlevel (void);
extern void exception_bound_range_exceeded_fault_lowlevel (void);
extern void exception_invalid_opcode_fault_lowlevel (void);
extern void exception_device_not_available_fault_lowlevel (void);
extern void exception_double_fault_lowlevel (void);
extern void exception_coprocessor_segment_overrun_abort_lowlevel (void);
extern void exception_invalid_tss_fault_lowlevel (void);
extern void exception_segment_not_present_fault_lowlevel (void);
extern void exception_stack_fault_lowlevel (void);
extern void exception_general_protection_fault_lowlevel (void);
extern void exception_page_fault_lowlevel (void);
extern void exception_dummy_lowlevel (void);
extern void exception_floating_point_error_fault_lowlevel (void);
extern void exception_alignment_check_fault_lowlevel (void);
extern void exception_machine_check_abort_lowlevel (void);

/* ...and the C functions. */
extern void exception_divide_error_fault (cpu_register_t registers);
extern void exception_debug_trap (cpu_register_t registers);
extern void exception_nmi (cpu_register_t registers);
extern void exception_breakpoint_trap (cpu_register_t registers);
extern void exception_overflow_trap (cpu_register_t registers);
extern void exception_bound_range_exceeded_fault (cpu_register_t registers);
extern void exception_invalid_opcode_fault (cpu_register_t registers);
extern void exception_device_not_available_fault (cpu_register_t registers);
extern void exception_double_fault (cpu_register_t registers);
extern void exception_coprocessor_segment_overrun_abort (cpu_register_t registers);
extern void exception_invalid_tss_fault (cpu_register_t registers);
extern void exception_segment_not_present_fault (cpu_register_t registers);
extern void exception_stack_fault (cpu_register_t registers);
extern void exception_general_protection_fault (cpu_register_t registers);
extern return_t exception_page_fault (cpu_register_t registers);
extern void exception_dummy (cpu_register_t registers);
extern void exception_floating_point_error_fault (cpu_register_t registers);
extern void exception_alignment_check_fault (cpu_register_t registers);
extern void exception_machine_check_abort (cpu_register_t registers);

#endif /* !__STORM_IA32_EXCEPTION_H__ */
