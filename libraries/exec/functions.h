/* $chaos: functions.h,v 1.1 2002/10/04 20:53:22 per Exp $ */
/* Abstract: Functions in the exec library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __EXEC_FUNCTIONS_H__
#define __EXEC_FUNCTIONS_H__

/* Lookup the first exec service provider. */
extern return_t exec_lookup (exec_service_t *exec);

/* Register an exec service provider. */
extern return_t exec_register (char *vendor, char *model, char *id,
                               service_info_t service_info);

#endif /* !__EXEC_FUNCTIONS_H__ */
