/* $chaos: lock.h,v 1.1 2002/06/24 20:00:26 per Exp $ */
/* Abstract: Locking functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/* Type definitions. */
/* A lock. */
typedef unsigned int lock_t;

/* Defines. */
#define LOCK_UNLOCKED                   1
#define LOCK_LOCKED                     0

/* Inline functions. */
/* Get the lock. */
static inline void lock (lock_t *locker)
{
    unsigned int eax;
    
    asm volatile ("movl $0, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl $0, %%eax\n"
                  "jne 1f\n"
                  "hlt\n"               /* This one is the key. */
                  "jmp 0b\n"
                  "1:"
                  : 
                  "=g" (*locker),
                  "=a" (eax)
                  :
                  "bcdDS" (*locker));
}

/* Get the look, from code that MAY BE run from an interrupt
   handler. */
static inline void lock_interrupt (lock_t *locker)
{
    unsigned int eax;
    
    asm volatile ("movl $0, %%eax\n"
                  "0:  xchgl %%eax, %0\n"
                  "cmpl $0, %%eax\n"
                  "je 0b\n"
                  : 
                  "=g" (*locker),
                  "=a" (eax)
                  :
                  "bcdDS" (*locker));
}

static inline void unlock (lock_t *locker)
{
    (*locker) = LOCK_UNLOCKED;
}
