/* $chaos: string.h,v 1.4 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file string.h
 * @brief Inlined string routines. 
 */

#ifndef __STORM_IA32_STRING_H__
#define __STORM_IA32_STRING_H__

/**
 * @brief               Copy a string.
 * @param destination   The destination string.
 * @param source        The source string.
 * @return              The destination string.
 */
static inline char *string_copy (char *destination, const char *source)
{
    int d0, d1, d2;
    asm volatile ("cld\n"
                  "1:  lodsb\n"
                  "stosb\n"
                  "testb %%al, %%al\n"
                  "jne 1b"
                  : 
                  "=&S" (d0), 
                  "=&D" (d1), 
                  "=&a" (d2)
                  :
                  "0" (source),
                  "1" (destination)
                  :
                  "memory");
    return destination;
}

/**
 * @brief               Copy a string, but no more than 'count' bytes.
 * @param destination   The destination string. 
 * @param source        The source string.
 * @param count         The maximum number of characters to copy.
 * @return              The destination string.
 */
static inline char *string_copy_max (char *destination, const char *source,
                                     unsigned int count)
{
    int esi, edi, ecx, eax;
    
    asm volatile ("cld\n"
                  "1:  decl %2\n"
                  "js 2f\n"
                  "lodsb\n"
                  "stosb\n"
                  "testb %%al, %%al\n"
                  "jne 1b\n"
                  "rep\n"
                  "stosb\n"
                  "2:"
                  : 
                  "=&S" (esi),
                  "=&D" (edi),
                  "=&c" (ecx),
                  "=&a" (eax)
                  : 
                  "0" (source),
                  "1" (destination),
                  "2" (count) 
                  : 
                  "memory");
    return destination;
}

/**
 * @brief               Compare two strings.
 * @param string1       The first string.
 * @param string2       The second string.
 * @return              0 if equal, negative if the first string is 'less'
 *                      than the second, or otherwise positive. 
 */
static inline int string_compare (const char *string1, const char *string2)
{
    int counter = -1;

    do 
    {
        counter++;

        if (string1[counter] < string2[counter]) 
        {
            return -1;
        }
        if (string1[counter] > string2[counter]) 
        {
            return 1;
        }
    } while (string1[counter] != '\0' && string2[counter] != '\0');
    
    return 0;
}

/**
 * @brief               Compare two strings, but no more than count characters.
 * @param string1       The first string.
 * @param string2       The second string.
 * @param count         The limit length.
 * @return              0 if equal, negative if the first string is 'less'
 *                      than the second, or otherwise positive.
 */
static inline int string_compare_max  (const char *string1,
                                       const char *string2,
                                       unsigned int count)
{
    register int eax;
    int esi, edi, ecx;
    
    asm volatile ("cld\n"
                  "1:  decl %3\n"
                  "js 2f\n"
                  "lodsb\n"
                  "scasb\n"
                  "jne 3f\n"
                  "testb %%al, %%al\n"
                  "jne 1b\n"
                  "2:  xorl %%eax, %%eax\n"
                  "jmp 4f\n"
                  "3:  sbbl %%eax, %%eax\n"
                  "orb $1, %%al\n"
                  "4:"
                  : 
                  "=a" (eax),
                  "=&S" (esi),
                  "=&D" (edi),
                  "=&c" (ecx)
                  :
                  "1" (string1),
                  "2" (string2),
                  "3" (count));
    
    return eax;
}

/**
 * @brief               Returns the string length.
 * @param string        The string.
 * @return              The string length. */
static inline unsigned int string_length (const char *string)
{
    int edi;
    register int return_value;
    
    asm volatile ("cld\n"
                  "repne\n"
                  "scasb\n"
                  "notl %0\n"
                  "decl %0"
                  :
                  "=c" (return_value),
                  "=&D" (edi)
                  :
                  "1" (string), 
                  "a" (0),
                  "0" (0xFFFFFFFF));
    return return_value;
}

/**
 * @brief               Returns the string length or size, whichever is smallest.
 * @param string        The string.
 * @param size          The maximum size.
 * @return              MIN(size, string_length(string))
 */
static inline unsigned int string_length_max (const char *string,
                                              unsigned int size)
{
    int edi;
    register int return_value;

    asm volatile ("movl %2, %0\n"
                  "jmp 2f\n"
                  "1: cmpb $0, (%0)\n"
                  "je 3f\n"
                  "incl %0\n"
                  "2: decl %1\n"
                  "cmpl $-1, %1\n"
                  "jne 1b\n"
                  "3: subl %2, %0"
                  :
                  "=a" (return_value),
                  "=&d" (edi)
                  :
                  "c" (string),
                  "1" (size));

    return return_value;
}

#endif /* !__STORM_IA32_STRING_H__ */
