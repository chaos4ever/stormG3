/* $chaos: storm.h,v 1.16 2002/10/11 07:45:18 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                storm.h
 * @brief               storm kernel API.
 *
 * This header file can be included by a kernel module that wants to
 * have access to kernel functions.
 *
 * FIXME: We really need to clean this mess up. Right now, we export
 * much that should not be exported... Rewrite this file from scratch.
 */

#ifndef __STORM_STORM_H__
#define __STORM_STORM_H__

#include <storm/defines.h>
#include <storm/module.h>
#include <storm/return_value.h>
#include <storm/types.h>
#include <storm/ia32/bit.h>
#include <storm/ia32/halt.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/memory_physical.h>
#include <storm/ia32/memory_virtual.h>
#include <storm/ia32/port.h>
#include <storm/ia32/process.h>
#include <storm/ia32/service.h>

/* Type definitions. */
typedef void (irq_handler_t)(unsigned int irq_level);

/* Function prototypes. */
/* Print a debug message. */
extern void debug_print (const char *format_string, ...);

/**
 * @brief               Dump the contents of a memory region.
 * @param memory        The address of the memory to dump.
 * @param length        The number of uint32s to dump.
 *
 * The memory is dumped in hexadecimal format.
 */
extern void debug_memory_dump (uint32_t *memory, unsigned int length);

/* Register the given DMA channel. */
extern return_t dma_register (unsigned int dma_channel, void **dma_buffer);

/* Register an IRQ for use by a module. */
extern return_t irq_register (unsigned int irq_number, char *description,
                              irq_handler_t *function);

/* Sleep for the given amount of milliseconds. */
extern return_t timer_sleep_milli (unsigned int time);

#endif /* !__STORM_STORM_H__ */
