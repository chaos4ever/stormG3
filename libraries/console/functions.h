/* $chaos: functions.h,v 1.1 2002/06/24 21:36:43 per Exp $ */
/* Abstract: Function definitions for the console library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LIBRARY_CONSOLE_FUNCTIONS_H__
#define __LIBRARY_CONSOLE_FUNCTIONS_H__

#include <storm/storm.h>
#include <console/console.h>

/* Lookup the first console service provider. */
extern return_t console_lookup (console_service_t *console);

#endif /* !__LIBRARY_CONSOLE_FUNCTIONS_H__ */
