/* $chaos: bit.h,v 1.8 2002/10/09 13:07:13 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file bit.h
 * @brief Bit manipulation macros. 
 *
 * This file is endian-specific and needs to be rewritten for
 * big-endian when we port to such a CPU. It provides very convenient
 * functions for reading and writing bit values to a integers, as well
 * as reading the upper/lower half of a 32-bit and 16-bit integer.
 */

#ifndef __STORM_IA32_BIT_H__
#define __STORM_IA32_BIT_H__

/** 
 * @brief Get the low 32 bits of a 64-bit integer variable. 
 */
#define LOW_32(x)                       ((x) & 0xFFFFFFFFUL)

/** 
 * @brief Get the high 32 bits of a 64-bit integer variable. 
 */
#define HIGH_32(x)                      ((x) >> 32)

/** 
 * @brief Get the low 16 bits of a 32-bit integer variable. 
 */
#define LOW_16(x)                       ((x) & 0xFFFF)

/** 
 * @brief Get the high 16 bits of a 32-bit integer variable. 
 */
#define HIGH_16(x)                      ((x) >> 16)

/**
 * @brief Get the low 8 bits of a 16-bit integer variable. 
 */
#define LOW_8(x)                        ((x) & 0xFF)

/**
 * @brief Get the high 8 bits of a 16-bit integer variable. 
 */
#define HIGH_8(x)                       ((x) >> 8)

// FIXME: Document this.
/* Bit manipulation macros. */
#define BIT_SET(a,b)                    ((a) |= (1 << (b)))
#define BIT_CLEAR(a,b)                  ((a) &= !(1 << (b)))
#define BIT_GET(a,b)                    ((a) & (1 << (b)) ? 1 : 0) 
#define BIT_IN_BYTES(a)                 ((a) % 8 != 0 ? (a) / 8 + 1 : (a) / 8)

/**
 * @brief Get the numeric value for bit x. 
 */
#define BIT_VALUE(x)                    (1 << (x))

#endif /* !__STORM_IA32_BIT_H__ */
