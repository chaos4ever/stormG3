/* $chaos: defines.h,v 1.5 2002/10/04 19:01:19 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file storm/defines.h
 * @brief Generic storm defines. 
 */

#ifndef __STORM_DEFINES_H__
#define __STORM_DEFINES_H__

/* Some standard defines. */
#undef NULL
#define NULL                            0
#define TRUE                            (1 == 1)
#define FALSE                           (!TRUE)

/* Some sizes. */
#define KIB                             (1024)
#define MIB                             (1024 * KIB)
#define GIB                             (1024 * MIB)

/* Use this define to attribute that the function will not ever return. */
#define NORETURN                        __attribute__ ((noreturn))

/* Use this define to tell the compiler that an argument or variable
   is not used. */
#define UNUSED                          __attribute__ ((unused))

/* The maximum number of servers to start at boot time. */
#define MAX_STARTUP_SERVERS             32

/* Stupid, but just to get the AVL code compiling. FIXME: Remove this ASAP. */
#define malloc(n) (NULL)
#define free(n)

#endif /* !__STORM_DEFINES_H__ */
