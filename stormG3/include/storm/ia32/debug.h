/* $chaos: debug.h,v 1.12 2002/10/08 20:13:22 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** @file debug.h
    @brief Functions used for debugging. */

#ifndef __STORM_IA32_DEBUG_H__
#define __STORM_IA32_DEBUG_H__

#include <storm/defines.h>
#include <storm/storm.h>
#include <storm/types.h>
#include <storm/ia32/gdb.h>

/* BSD rules. :-) */
#ifdef NETBSD_COLORS
#  define DEBUG_ATTRIBUTE_TEXT           0x02
#  define DEBUG_ATTRIBUTE_BACKGROUND     0x07
#else
# if defined(FREEBSD_COLORS)
#  define DEBUG_ATTRIBUTE_TEXT           0x0F
#  define DEBUG_ATTRIBUTE_BACKGROUND     0x07
# else /* OpenBSD is the default. */
#  define DEBUG_ATTRIBUTE_TEXT            0x17
#  define DEBUG_ATTRIBUTE_BACKGROUND      0x07
# endif
#endif

/**
 * @brief The width (in characters) of the screen.
 */
#define DEBUG_SCREEN_WIDTH              80

/**
 * @brief The height (in characters9 of the screen.
 */
#define DEBUG_SCREEN_HEIGHT             25

/**
 * @brief The physical base address of the screen. 
 */
#define BASE_SCREEN                     (0xB8000)

/**
 * @brief Easy EGA screen access. 
 */
typedef struct
{ 
    /**
     * @brief The character of this location.
     */
    char character;

    /**
     * @brief The attribute of this character.
     */
    uint8_t attribute;
} debug_screen_type __attribute__ ((packed));

/**
 * @brief Initialize debugging code. 
 */
extern void debug_init (void);

/**
 * @brief               Dump the contents of a memory region.
 * @param memory        The address of the memory to dump.
 * @param length        The number of uint32s to dump.
 *
 * The memory is dumped in hexadecimal format.
 */
extern void debug_memory_dump (uint32_t *memory, unsigned int length);

/* Macros. */
#define DEBUG_HALT(message) \
  debug_print (message); \
  debug_print (" (%s:%u)\n", __FILE__, __LINE__); \
  while (TRUE);

#endif /* !__STORM_IA32_DEBUG_H__ */
