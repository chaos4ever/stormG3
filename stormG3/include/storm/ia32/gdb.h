/* $chaos: gdb.h,v 1.4 2002/10/10 14:09:12 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file        gdb.h
 * @brief       GDB support. 
 *
 * Setting up remote debugging with GDB is pretty easy. First you
 * enable GDB code in the kernel:
 *
 * cons gdb=0,115200
 *
 * And then you run (while booting the kernel on the machine connected
 * via a null modem cable):
 *
 * gdb -x remote.gdb source/ia32/stormG3
 *
 * If your serial port is something else than ttyS0 (COM1), you need
 * to modify remote.gdb and/or the cons command line. remote.gdb is
 * the setting on your GDB server, and the cons setting is the com
 * port on the machine running stormG3.
 */

#ifndef __STORM_IA32_GDB_H__
#define __STORM_IA32_GDB_H__

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
