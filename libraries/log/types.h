/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Log library types. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LIBRARY_LOG_TYPES_H__
#define __LIBRARY_LOG_TYPES_H__

/* Functions in the log service provider. */
typedef return_t (*log_print_t)(unsigned int, char *);
typedef return_t (*log_print_formatted_t)(unsigned int, char *, ...);

/* A log service. */
typedef struct
{
    /* The log magic cookie. */
    unsigned int magic_cookie;

    /* The function log_print. */
    log_print_t print;

    /* The function log_print_formatted. */
    log_print_formatted_t print_formatted;
} log_service_t;

/* Initialization function. */
typedef return_t (*log_init_t)(log_service_t *);

#endif /* !__LIBRARY_LOG_TYPES_H__ */
