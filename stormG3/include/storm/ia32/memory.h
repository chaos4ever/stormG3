/* $chaos: memory.h,v 1.7 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file memory.h
 * @brief Memory operations. 
 */

#ifndef __STORM_IA32_MEMORY_H__
#define __STORM_IA32_MEMORY_H__

#include <storm/types.h>

/* Inlines. */
static inline void *memory_copy (void *to, const void *from, unsigned int size)
{
    int ecx, edi, esi;
    
    asm volatile ("cld\n"
                  "rep ; movsl\n"
                  "testb $2, %b4\n"
                  "je 1f\n"
                  "movsw\n"
                  "1: testb $1, %b4\n"
                  "je 2f\n"
                  "movsb\n"
                  "2:"
                  : 
                  "=&c" (ecx), 
                  "=&D" (edi), 
                  "=&S" (esi)
                  :
                  "0" (size / 4),
                  "q" (size),
                  "1" ((long) to),
                  "2" ((long) from)
                  : 
                  "memory");
    
    return (to);
}

static inline void memory_set_uint8 (uint8_t *address, uint8_t c,
                                     unsigned int size)
{
    int ecx, edi;
    
    asm volatile ("cld\n"
                  "rep\n"
                  "stosb"
                  :
                  "=&c" (ecx),
                  "=&D" (edi)
                  : 
                  "a" (c),
                  "1" (address),
                  "0" (size)
                  : 
                  "memory");
}

static inline void memory_set_uint16 (uint16_t *address, uint16_t c,
                                      unsigned int size)
{
    int ecx, edi;

    asm volatile  ("cld\n"
                   "rep\n"
                   "stosw"
                   : 
                   "=&c" (ecx),
                   "=&D" (edi)
                   : 
                   "a" (c),
                   "1" (address),
                   "0" (size)
                   :
                   "memory");
}

static inline void memory_set_uint32 (uint32_t *address, uint32_t c,
                                      unsigned int size)
{
    int ecx, edi;

    asm volatile  ("cld\n"
                   "rep\n"
                   "stosl"
                   : 
                   "=&c" (ecx),
                   "=&D" (edi)
                   : 
                   "a" (c),
                   "1" (address),
                   "0" (size)
                   :
                   "memory");
}

#endif /* !__STORM_IA32_MEMORY_H__ */
