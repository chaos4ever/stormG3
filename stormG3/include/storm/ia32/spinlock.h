/* $chaos: spinlock.h,v 1.2 2002/10/04 19:01:20 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file spinlock.h
 * @brief Kernel locking. 
 */

#ifndef __STORM_IA32_SPINLOCK_H__
#define __STORM_IA32_SPINLOCK_H__

/* Type definitions. */
typedef unsigned int spinlock_t;

/* Enumerations. */
enum
{
    SPIN_LOCKED,
    SPIN_UNLOCKED
};

/* Lock the given spinlock. This function loops until it may access
   the semaphores, and then locks them. */
static inline void spin_lock (spinlock_type spinlock)
{
    unsigned int eax;
    
    asm volatile ("movl $0, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl $0, %%eax\n"
                  "je 0b"
                  :
                  "=g" (spinlock),
                  "=a" (eax)
                  :
                  "bcdDS" (spinlock));
}

/* Unlock a mutex which has previously been locked with
   mutex_lock. */
static inline void spin_unlock (spinlock_type spinlock)
{
    spinlock = SPIN_UNLOCKED;
}

#endif /* !__STORM_IA32_SPINLOCK_H__ */
