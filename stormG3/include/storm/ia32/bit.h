/* $chaos: bit.h,v 1.5 2002/06/18 19:32:26 per Exp $ */
/* Abstract: Bit manipulation macros. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_BIT_H__
#define __STORM_IA32_BIT_H__

/* This file is endian-specific. */

/* Get the low or high 16 bits of a 32-bit integer
   variable. */
#define LOW_16(x)                       ((x) & 0xFFFF)
#define HIGH_16(x)                      ((x) >> 16)

/* Get the low or high 8 bits of a 16-bit integer variable. */
#define LOW_8(x)                        ((x) & 0xFF)
#define HIGH_8(x)                       ((x) >> 8)

/* Bit manipulation macros. */
#define BIT_SET(a,b)                    ((a) |= (1 << (b)))
#define BIT_CLEAR(a,b)                  ((a) &= !(1 << (b)))
#define BIT_GET(a,b)                    ((a) & (1 << (b)) ? 1 : 0) 
#define BIT_IN_BYTES(a)                 ((a) % 8 != 0 ? (a) / 8 + 1 : (a) / 8)

/* Get the numeric value for bit x. */
#define BIT_VALUE(x)                    (1 << (x))

#endif /* !__STORM_IA32_BIT_H__ */
