/* $chaos: gdb.h,v 1.2 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file gdb.h
 * @brief GDB support. 
 */

#ifndef __STORM_IA32_GDB_H__
#define __STORM_IA32_GDB_H__

#define BREAKPOINT() asm("int $3");
extern void gdb_serial_init (unsigned short port, unsigned int speed);
extern void gdb_set_debug_traps (void);

#endif /* !__STORM_IA32_GDB_H__ */
