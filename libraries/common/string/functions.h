/* $chaos: functions.h,v 1.1 2002/06/23 20:33:12 per Exp $ */
/* Abstract: Function prototypes. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LIBRARY_STRING_FUNCTIONS_H__
#define __LIBRARY_STRING_FUNCTIONS_H__

#include <stdarg.h>

extern return_t string_to_number (const char *string, int *number,
                                  int *characters);

extern return_t string_print (char *output, const char *format_string, ...)
  __attribute__ ((format (printf, 2, 3)));
extern return_t string_print_va (char *output, const char *format_string,
                                 va_list arguments);

#endif /* !__LIBRARY_STRING_FUNCTIONS_H__ */
