/* $chaos: console_output.h,v 1.3 2002/05/23 11:23:56 per Exp $ */
/* Abstract: Console outputting functions. */
/* Authors: Henrik Hallin <hal@chaosdev.org> 
            Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

/* Functions. */
#ifndef __CONSOLE_OUTPUT_H__
#define __CONSOLE_OUTPUT_H__

#include "console.h"

extern void console_output (console_t *console, const char *string);

#endif /* !__CONSOLE_OUTPUT_H__ */
