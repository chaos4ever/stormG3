/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Definition of the log protocol. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LOG_LOG_H__
#define __LOG_LOG_H__

#include <storm/storm.h>

// FIXME: Have this be unique.
#define LOG_COOKIE                      0x12345678

enum
{
    /* Emergency messages are to be printed when the program has
       encountered a serious error which forces termination. */
    LOG_URGENCY_EMERGENCY,
    
    /* Something is wrong, but execution may continue. */
    LOG_URGENCY_ERROR,
    
    /* Something might be wrong, but we are not entirely sure. */
    LOG_URGENCY_WARNING,
    
    /* Typical informative messages are showing which hardware we
       detected, etc. */
    LOG_URGENCY_INFORMATIVE,
    
    /* Debug messages are for debugging purposes only -- normally, they
       can be safely ignored. Eventually, they will be removed. */
    LOG_URGENCY_DEBUG
};

/* Different function pointer types. */
typedef return_t (*log_print_t)(unsigned int, char *);
typedef return_t (*log_init_t)(void *);

/* A log service. */
typedef struct
{
    /* The log magic cookie. */
    unsigned int magic_cookie;

    /* The function log_print. */
    log_print_t print;
} log_service_t;

#endif /* !__LOG_LOG_H__ */
