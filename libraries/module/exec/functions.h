/* $chaos: functions.h,v 1.3 2002/11/15 19:34:56 per Exp $ */
/* Abstract: Functions in the exec library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __EXEC_FUNCTIONS_H__
#define __EXEC_FUNCTIONS_H__

/* Lookup the first exec service provider. */
extern return_t exec_lookup (exec_service_t *exec);

/* Register an exec service provider. */
extern return_t exec_register (service_register_t *service_register_info,
                               service_method_t *service_method);

#endif /* !__EXEC_FUNCTIONS_H__ */
