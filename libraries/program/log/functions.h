/* $chaos: dotfile.emacs,v 1.43 2002/11/14 20:15:09 per Exp $ */
/* Abstract: Log library functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             log/functions.h
 * @brief            Log library functions.
 */

#ifndef __LIBRARY_LOG_FUNCTIONS_H__
#define __LIBRARY_LOG_FUNCTIONS_H__

/**
 * @brief               Handy function for connecting to the first
 *                      available log service.
 * @param log           Pointer to a structure where the connection
 *                      information will be stored.
 * @return              LOG_RETURN_SUCCESS if successful.
 */
extern return_t log_init (log_service_t *log);

#endif /* !__LIBRARY_LOG_FUNCTIONS_H__ */
