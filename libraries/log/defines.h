/* $chaos: defines.h,v 1.2 2002/10/04 19:00:55 per Exp $ */
/* Abstract: Log library defines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LOG_DEFINES_H__
#define __LOG_DEFINES_H__

// FIXME: Have this be unique.
#define LOG_COOKIE                      0x12345678

/* Major log service version. */
#define LOG_SERVICE_MAJOR_VERSION \
                        (0)

/* Minor log service version. */
#define LOG_SERVICE_MINOR_VERSION \
                        (1)

enum log_urgency_t
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

#endif /* !__LOG_DEFINES_H__ */
