/* $chaos: types.h,v 1.3 2002/10/09 08:32:02 per Exp $ */
/* Abstract: Kernel library types. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __KERNEL_TYPES_H__
#define __KERNEL_TYPES_H__

/* Log the given string to the kernel log. */
typedef return_t (*kernel_log_t)(const char *string);

typedef struct
{
    /* The kernel magic cookie. */
    unsigned int magic_cookie;

    /* Log. */
    kernel_log_t log;
} kernel_service_t;

#endif /* !__KERNEL_TYPES_H__ */
