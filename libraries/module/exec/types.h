/* $chaos: types.h,v 1.2 2002/10/04 21:24:19 per Exp $ */
/* Abstract: Exec library types. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __EXEC_TYPES_H__
#define __EXEC_TYPES_H__

/* Run the given program. */
typedef return_t (*exec_run_t)(void *program);

// TODO: typedef return_t (*exec_load_library_t)(void *library);

typedef struct
{
    /* The block magic cookie. */
    unsigned int magic_cookie;

    /* Run a program. */
    exec_run_t run;
} exec_service_t;

#endif /* !__EXEC_TYPES_H__ */
