/* $chaos: system_call.h,v 1.2 2002/10/24 22:13:08 per Exp $ */
/* Abstract: System call prototypes etc. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                system_call.h
 * @brief               System call implementation.
 */

#ifndef __STORM_IA32_SYSTEM_CALL_H__
#define __STORM_IA32_SYSTEM_CALL_H__

/**
 * @brief               The system call vector in the IDT. 
 */
#define SYSTEM_CALL_IDT_ENTRY \
                        (0x88)

/* Only in the kernel. */
#ifdef __STORM_KERNEL__

/**
 * @brief               Set up the system call in the IDT.
 */
extern void system_call_init (void);

/**
 * @brief               The low-level system call handler.
 */
extern void system_call_lowlevel (void);

/**
 * @brief               The high-level system call handler.
 * @param stack         The callers stack (with the parameters to the
 *                      system call).
 * @return              The return value of the system call.
 */
extern return_t system_call (uint32_t *stack);

#endif /* __STORM_KERNEL__ */

#if (! defined __STORM_KERNEL__ ) && (! defined __STORM_KERNEL_MODULE__)

/* Lookup a service by name, vendor, model and ID. */
static inline unsigned int system_call_service_lookup (service_lookup_t *service_lookup, size_t *services, service_t **out_service)
{
    unsigned int return_value;

    asm volatile ("pushl        %1\n"   /* out_service */
                  "pushl        %2\n"   /* services */
                  "pushl        %3\n"   /* service_lookup */

                  "pushl        %4\n"   /* number of arguments. */
                  "pushl        %5\n"   /* system call number. */
                  "int          %9"
                  : 
                  "=a" (return_value)
                  :
                  "g" (out_service),
                  "g" (services),
                  "g" (service_lookup),
                  "g" (3),              /* number of arguments. */
                  "g" (SYSTEM_CALL_SERVICE_LOOKUP),
                  "N" (SYSTEM_CALL_IDT_ENTRY));
    return return_value;
}


#endif /* (! defined __STORM_KERNEL__ ) &&
          (! defined __STORM_KERNEL_MODULE__) */

#endif /* !__STORM_IA32_SYSTEM_CALL_H__ */
