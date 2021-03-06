/* $chaos: memory.h,v 1.1 2002/12/12 22:03:24 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                memory/inlines.h
 * @brief               Inline functions in the memory library. 
 *
 * Inlined functions for simple and small (but very useful) memory
 * operations.
 */

#ifndef __LIBRARY_MEMORY_INLINES_H__
#define __LIBRARY_MEMORY_INLINES_H__

#include <storm/storm.h>

/**
 * @brief               Copy between memory areas.
 * @param to            The source.
 * @param from          The destination.
 * @param size          The number of bytes to copy. 
 */
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

/**
 * @brief               Set memory to the given uint8.
 * @param address       The address of the memory to set.
 * @param value         The value to set.
 * @param count         The number of uint8s to set. 
 */

static inline void memory_set_uint8 (uint8_t *address, uint8_t value,
                                     unsigned int count)
{
    int ecx, edi;
    
    asm volatile ("cld\n"
                  "rep\n"
                  "stosb"
                  :
                  "=&c" (ecx),
                  "=&D" (edi)
                  : 
                  "a" (value),
                  "1" (address),
                  "0" (count)
                  : 
                  "memory");
}

/**
 * @brief               Set memory to the given uint16.
 * @param address       The address of the memory to set.
 * @param value         The value to set.
 * @param count         The number of uint16s to set. 
 */
static inline void memory_set_uint16 (uint16_t *address, uint16_t value,
                                      unsigned int count)
{
    int ecx, edi;

    asm volatile ("cld\n"
                  "rep\n"
                  "stosw"
                  : 
                  "=&c" (ecx),
                  "=&D" (edi)
                  : 
                  "a" (value),
                  "1" (address),
                  "0" (count)
                  :
                  "memory");
}

/**
 * @brief               Set memory to the given uint32.
 * @param address       The address of the memory to set.
 * @param value         The value to set.
 * @param count         The number of uint32s to set. 
 */
static inline void memory_set_uint32 (uint32_t *address, uint32_t value,
                                      unsigned int count)
{
    int ecx, edi;

    asm volatile  ("cld\n"
                   "rep\n"
                   "stosl"
                   : 
                   "=&c" (ecx),
                   "=&D" (edi)
                   : 
                   "a" (value),
                   "1" (address),
                   "0" (count)
                   :
                   "memory");
}

/**
 * @brief               Clear (zero out) a page.
 * @param address       The base address of the page to clear.
 */
static inline void memory_clear_page (void *address)
{
    memory_set_uint32 ((uint32_t *) address, 0, PAGE_SIZE / 4);
}

#endif /* !__LIBRARY_MEMORY_INLINES_H__ */
