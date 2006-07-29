/* $chaos: debug.h,v 1.15 2002/10/15 21:57:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** @file               debug.h
    @brief              Functions used for debugging. */

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
 * @brief               The width (in characters) of the screen.
 */
#define DEBUG_SCREEN_WIDTH \
                        80

/**
 * @brief               The height (in characters9 of the screen.
 */
#define DEBUG_SCREEN_HEIGHT \
                        25

/**
 * @brief               The physical base address of the screen. 
 */
#define BASE_SCREEN     (0xB8000)

/**
 * @brief               Easy EGA screen access. 
 */
typedef struct PACKED
{ 
    /**
     * @brief           The character of this location.
     */
    char character;

    /**
     * @brief           The attribute of this character.
     */
    uint8_t attribute;
} debug_screen_type;

/**
 * @brief               Initialize debugging code. 
 */
extern void debug_init (void);

/* Macros. */
/**
 * @brief               Halt the system completely.
 * @param message       A message to print.
 * @return              Does not return.
 */
#define DEBUG_HALT(message) \
  debug_print (message); \
  debug_print (" (%s:%u)\n", __FILE__, __LINE__); \
  while (TRUE);

/* 
 * @brief               Print debugging information.
 *
 * Add this macro somewhere and the kernel will print very handy
 * information whenever that line is being reached. 
 */
#define DEBUG_INFO() \
  debug_print ("Passed %s:%u (%s)\n", __FILE__, __LINE__, __FUNCTION__);

/**
 * @brief               A breakpoint.
 *
 * You can add a breakpoint in the code just by running this
 * macro. When you then load the kernel with serial debugging enabled,
 * the debugger will break on this point. If serial debugging is not
 * enabled, the built-in kernel breakpoint handler will be called
 * which will basically just print a message (so that you know that
 * you have a breakpoint in the code that should be removed when
 * compiling a release).
 */
#define DEBUG_BREAKPOINT() \
                        asm("int $3");

#endif /* !__STORM_IA32_DEBUG_H__ */
