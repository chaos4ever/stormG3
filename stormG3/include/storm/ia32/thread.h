/* $chaos: thread.h,v 1.6 2002/10/17 21:07:58 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                thread.h
 * @brief               Thread support. 
 */

#ifndef __STORM_IA32_THREAD_H__
#define __STORM_IA32_THREAD_H__

#include <storm/ia32/spinlock.h>
#include <storm/ia32/tss.h>

/**
 * @brief               The thread ID of the kernel thread. (idle 
 *                      thread) 
 */
#define THREAD_ID_KERNEL \
                        0

#endif /* !__STORM_IA32_THREAD_H__ */
