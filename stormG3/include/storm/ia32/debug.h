/* $chaos: xemacs-script,v 1.6 2002/05/24 17:34:57 per Exp $ */
/* Abstract: Debug declarations. */
/* Author: Per Lundberg <per@halleluja.nu> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_DEBUG_H__
#define __STORM_IA32_DEBUG_H__

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

extern void debug_init (void);
extern void debug_print (const char *format_string, ...);

#endif /* !__STORM_IA32_DEBUG_H__ */
