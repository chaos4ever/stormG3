/* $chaos: memory.h,v 1.1 2002/05/25 20:09:39 per Exp $ */
/* Abstract: Memory operations. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_MEMORY_H__
#define __STORM_IA32_MEMORY_H__

#include <storm/types.h>

/* Inlines. */
/* FIXME: These are not all nice. */
static inline void *memory_copy (void *to, void *from, int n)
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
                  "0" (n / 4),
                  "q" (n),
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

static inline void memory_set_uint16 (uint16_t *addr, uint16_t c,
                                      unsigned int size)
{
    int d0, d1;

    asm volatile  ("cld\n"
                   "rep\n"
                   "stosw"
                   : 
                   "=&c" (d0),
                   "=&D" (d1)
                   : 
                   "a" (c),
                   "1" (addr),
                   "0" (size)
                   :
                   "memory");
}

#endif /* !__STORM_IA32_MEMORY_H__ */
