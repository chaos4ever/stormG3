/* $chaos: debug.h,v 1.4 2002/06/12 19:28:21 per Exp $ */
/* Abstract: Debug declarations. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_DEBUG_H__
#define __STORM_IA32_DEBUG_H__

#include <storm/defines.h>
#include <storm/types.h>

/* OpenBSD rules. */
#define DEBUG_ATTRIBUTE_TEXT            0x17
#define DEBUG_ATTRIBUTE_BACKGROUND      0x07

#define DEBUG_SCREEN_WIDTH              80
#define DEBUG_SCREEN_HEIGHT             25
#define BASE_SCREEN                     (0xB8000)

/* Typedefs. */
typedef struct
{ 
  char character;
  uint8_t attribute;
} __attribute__ ((packed)) debug_screen_type;

/* Initialize debugging code. */
extern void debug_init (void);

/* Print a debug message. */
extern void debug_print (const char *format_string, ...);

/* Dump memory. */
extern void debug_memory_dump (uint32_t *memory, unsigned int length);

/* Macros. */
#define DEBUG_HALT(message) \
  debug_print (message); \
  debug_print ("(%s:%s)\n", __FILE__, __LINE__); \
  while (TRUE);

#endif /* !__STORM_IA32_DEBUG_H__ */
