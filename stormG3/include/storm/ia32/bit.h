/* $chaos: bit.h,v 1.1 2002/05/25 20:09:39 per Exp $ */
/* Abstract: Bit manipulation macros. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_BIT_H__
#define __STORM_IA32_BIT_H__

#define BIT_SET(a,b) ((a) |= (1 << (b)))
#define BIT_CLEAR(a,b) ((a) &= !(1 << (b)))
#define BIT_GET(a,b) ((a) & (1 << (b)) ? 1 : 0) 
#define BIT_IN_BYTES(a) ((a) % 8 != 0 ? (a) / 8 + 1 : (a) / 8)

/* Get the numeric value for bit x. */
#define BIT_VALUE(x) (1 << (x))

#endif /* !__STORM_IA32_BIT_H__ */
