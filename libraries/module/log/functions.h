/* $chaos: functions.h,v 1.4 2002/11/20 20:04:31 per Exp $ */
/* Abstract: Log library functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LIBRARY_LOG_FUNCTIONS_H__
#define __LIBRARY_LOG_FUNCTIONS_H__

/* Lookup the first log service provider. */
extern return_t log_lookup (log_service_t *log);

/* Register a log service provider. */
extern return_t log_register (service_register_t *service_register_info,
                              service_method_t *service_method);

#endif /* !__LIBRARY_LOG_FUNCTIONS_H__ */
