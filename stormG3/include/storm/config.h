/* $chaos: config.h,v 1.2 2002/06/05 18:17:42 per Exp $ */
/* Abstract: Kernel configuration. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_CONFIG_H__
#define __STORM_CONFIG_H__

#define STORM_VERSION   "G3 0.0.1"

/* Add a GDB breakpoint for remote debugging. Define if you have it
   set up proper. */
#undef GDB_INCLUDE

/* Change these if you like. */
#define GDB_PORT        0
#define GDB_SPEED       115200

#endif /* !__STORM_CONFIG_H__ */
