/* $chaos: functions.h,v 1.2 2002/08/09 05:59:39 per Exp $ */
/* Abstract: Function definitions for the console library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LIBRARY_CONSOLE_FUNCTIONS_H__
#define __LIBRARY_CONSOLE_FUNCTIONS_H__

#include <storm/storm.h>
#include <console/console.h>

/* Lookup the first console service provider. */
extern return_t console_lookup (console_service_t *console);

/* Register a console service provider. */
extern return_t console_register (service_register_t *service_register_info,
                                  service_method_t *service_method);

#endif /* !__LIBRARY_CONSOLE_FUNCTIONS_H__ */
