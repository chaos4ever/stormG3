/* $chaos: functions.h,v 1.1 2002/12/17 21:48:13 per Exp $ */
/* Abstract: Console library functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             console/functions.h
 * @brief            Console library functions.
 */

#ifndef __LIBRARY_CONSOLE_FUNCTIONS_H__
#define __LIBRARY_CONSOLE_FUNCTIONS_H__

/**
 * @brief               Handy function for connecting to the first
 *                      available console service.
 * @param kernel        Pointer to a structure where the connection
 *                      information will be stored.
 * @return              CONSOLE_RETURN_SUCCESS if successful.
 */
extern return_t console_init (console_service_t *console);

#endif /* !__LIBRARY_CONSOLE_FUNCTIONS_H__ */
