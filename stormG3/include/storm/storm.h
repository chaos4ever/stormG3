/* $chaos: storm.h,v 1.3 2002/06/17 20:58:28 per Exp $ */
/* Abstract: storm kernel API. This header file can be included by a
   kernel module that wants to have access to kernel functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_STORM_H__
#define __STORM_STORM_H__

#include <storm/defines.h>
#include <storm/module.h>
#include <storm/return_value.h>
#include <storm/types.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/port.h>

/* Type definitions. */
typedef void (irq_handler_t)(unsigned int irq_level);

/* Print a debug message. */
extern void debug_print (const char *format_string, ...);

/* Register an IRQ for use by a module. */
extern return_t irq_register (unsigned int irq_number, char *description,
                              irq_handler_t *function);

#endif /* !__STORM_STORM_H__ */
