/* $chaos: log.h,v 1.1 2002/12/03 14:32:02 johannes Exp $ */
/* Abstract: Definitions for the log protocol. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             log.h
 * @brief            Definition of the log protocol.
 */

#ifndef __PROTOCOL_LOG_H__
#define __PROTOCOL_LOG_H__

/* A magic cookie, to make sure this is really a log service
   provider. FIXME: Let this be truly unique. */
#define LOG_COOKIE              0x12345678

/* The major version of the block service. Bump this one step when you
   make CHANGES to the block service API that will make it
   incompatible with old programs. */
#define LOG_PROTOCOL_MAJOR_VERSION \
                        (0)

/* The minor version of the block service. Should be bumped whenever a
   function is added to the API that DOES NOT break the binary
   compatibility with previously compiled programs. */
#define LOG_PROTOCOL_MINOR_VERSION \
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

#endif /* !__PROTOCOL_LOG_H__ */
