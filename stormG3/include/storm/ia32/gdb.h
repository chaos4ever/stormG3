/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: GDB support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_GDB_H__
#define __STORM_IA32_GDB_H__

#define BREAKPOINT() asm("int $3");
extern void gdb_serial_init (unsigned short port, unsigned int speed);
extern void gdb_set_debug_traps (void);

#endif /* !__STORM_IA32_GDB_H__ */
