/* $chaos: gdb.h,v 1.3 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file        gdb.h
 * @brief       GDB support. 
 */

#ifndef __STORM_IA32_GDB_H__
#define __STORM_IA32_GDB_H__

/**
 * @brief               A breakpoint.
 *
 * You can add a breakpoint in the code just by running this
 * macro. When you then load the kernel with serial debugging enabled,
 * the debugger will break on this point.
 */
#define BREAKPOINT() asm("int $3");

/**
 * @brief               Initialize serial GDB debugging.
 * @param port          The number of the serial port to use.
 * @param speed         The speed to use.
 */
extern void gdb_serial_init (unsigned short port, unsigned int speed);

/**
 * @brief               Set up GDB debug traps.
 * 
 * These traps replace the ordinary exception handlers, and instead of
 * showing a crash screen, they give control over to GDB.
 */
extern void gdb_set_debug_traps (void);

#endif /* !__STORM_IA32_GDB_H__ */
