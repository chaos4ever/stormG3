/* $chaos: spinlock.h,v 1.7 2002/10/23 21:02:47 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                spinlock.h
 * @brief               Kernel locking. 
 */

#ifndef __STORM_IA32_SPINLOCK_H__
#define __STORM_IA32_SPINLOCK_H__

/* Things not available to userspace. */
#if (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__)

/**
 * @brief               The setting of a lock.
 */
enum spinlock_t
{
    /**
     * @brief           The lock is unlocked.
     */
    SPIN_UNLOCKED,

    /**
     * @brief           The lock is locked.
     */
    SPIN_LOCKED
};

// FIXME: Don't hardcode $1 here, but use SPIN_LOCKED.
/** 
 * @brief               Get the lock. 
 * @param lock          The lock to get.
 */
static inline void spin_lock (spinlock_t *lock)
{
    unsigned int eax;
    
    asm volatile ("movl $1, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl $1, %%eax\n"
                  "jne 1f\n"
                  "hlt\n"               /* This one is the key. */
                  "jmp 0b\n"
                  "1:"
                  : 
                  "=g" (*lock),
                  "=a" (eax)
                  :
                  "bcdDS" (*lock));
}

/**
 * @brief               Get the look, from code that MAY BE run from
 *                      within an interrupt handler. 
 * @param lock          The lock to get.
 *
 */
static inline void spin_lock_interrupt (spinlock_t *lock)
{
    unsigned int eax;
    
    asm volatile ("movl $1, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl $1, %%eax\n"
                  "je 0b\n"
                  : 
                  "=g" (*lock),
                  "=a" (eax)
                  :
                  "bcdDS" (*lock));
}

/**
 * @brief               Unlock a spinlock which has previously been 
 *                      locked with spin_lock. 
 * @param lock          The lock to unlock.
 */
static inline void spin_unlock (spinlock_t *lock)
{
    *lock = SPIN_UNLOCKED;
}

#endif /* (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__) */

#endif /* !__STORM_IA32_SPINLOCK_H__ */
