/* $chaos: types.h,v 1.1 2002/12/12 21:59:41 per Exp $ */
/* Abstract: Log library types. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LIBRARY_LOG_TYPES_H__
#define __LIBRARY_LOG_TYPES_H__

/*
 * @brief               Functions in the log service. 
 */
typedef return_t (*log_print_t)(unsigned int, char *);
typedef return_t (*log_print_formatted_t)(unsigned int, char *, ...);

/**
 * @brief               A log service. 
 */
typedef struct
{
    /**
     * @brief           The log magic cookie. */
    unsigned int magic_cookie;

    /**
     * @brief           The function log_print. 
     */
    log_print_t print;

    /**
     * @brief           The function log_print_formatted. 
     */
    log_print_formatted_t print_formatted;
} log_service_t;

#endif /* !__LIBRARY_LOG_TYPES_H__ */
