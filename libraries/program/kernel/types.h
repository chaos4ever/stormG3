/* $chaos: types.h,v 1.1 2002/12/17 21:48:02 per Exp $ */
/* Abstract: Kernel library types. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LIBRARY_KERNEL_TYPES_H__
#define __LIBRARY_KERNEL_TYPES_H__

/**
 * @brief               Set the name of the current process.
 */
typedef return_t (*kernel_set_process_name_t)(const char *name);

/**
 * @brief               Set the name of the current thread.
 */
typedef return_t (*kernel_set_thread_name_t)(const char *name);

/**
 * @brief               A kernel service. 
 */
typedef struct
{
    /**
     * @brief           The kernel magic cookie. 
     */
    unsigned int magic_cookie;

    /**
     * @brief           Set the process name.
     */
    kernel_set_process_name_t
                        set_process_name;

    /**
     * @brief           Set the thread name.
     */
    kernel_set_thread_name_t
                        set_thread_name;
} kernel_service_t;

#endif /* !__LIBRARY_KERNEL_TYPES_H__ */
