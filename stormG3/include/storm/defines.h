/* $chaos: defines.h,v 1.14 2002/10/24 21:35:39 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                storm/defines.h
 * @brief               Generic storm defines. 
 */

#ifndef __STORM_DEFINES_H__
#define __STORM_DEFINES_H__

#undef NULL
/**
 * @brief               A pointer to the lowest accessible memory address.
 *
 * This address is not mapped. Therefore, it may be used for
 * specifying an "empty pointer", pointing to nothing -- a very common
 * programming practice.
 */
#define NULL            ((void *) 0)

/**
 * @brief               A true boolean value.
 */
#define TRUE            (1 == 1)

/**
 * @brief               A false boolean value.
 */
#define FALSE           (!TRUE)

/**
 * @brief               The minimum of the two values.
 */
#define MIN(a,b)        ((a) < (b) ? (a) : (b))

/**
 * @brief               The maximum of the two values.
 */
#define MAX(a,b)        ((a) > (b) ? (a) : (b))

/**
 * @brief               A kibibyte.
 */
#define KIB             (1024U)

/**
 * @brief               A mibibyte.
 */
#define MIB             (1024U * KIB)

/**
 * @brief               A gibibyte.
 */
#define GIB             (1024U * MIB)

/**
 * @brief               The stack base for the process.
 */
#define STACK_BASE      0

/**
 * @brief               Use this define to attribute that the function
 *                      will not ever return. 
 */
#define NORETURN        __attribute__ ((noreturn))

/**
 * @brief               Use this define to tell the compiler that an
 *                      argument or variable is not used. 
 */
#define UNUSED          __attribute__ ((unused))

/**
 * @brief               Use this define to mark a function as deprecated.
 */
#define DEPRECATED      __attribute__ ((deprecated))

/**
 * @brief               Use this define to tell the compiler that a
 *                      structure should be packed.
 * 
 * A packed structure uses no padding, which may otherwise be put in
 * by the compiler to get a certain alignment on the data. For some
 * structures that are locked to a specific format (for example a
 * binary file format), such practices are directly harmful and you
 * need to mark such structures as PACKED for the code to work
 * properly..
 */
#define PACKED          __attribute__ ((packed))

/**
 * @brief               The maximum number of servers to start at boot time. 
 */
#define MAX_STARTUP_SERVERS \
                        (32)

/**
 * @brief               The length of a service name.
 */
#define SERVICE_NAME_LENGTH \
                        (32)

/**
 * @brief               The length of a vendor name.
 */
#define SERVICE_VENDOR_LENGTH \
                        (32)

/**
 * @brief               The length of a model name.
 */
#define SERVICE_MODEL_LENGTH \
                        (32)

/**
 * @brief               The length of a unique service ID.
 */
#define SERVICE_ID_LENGTH \
                        (16)

/* Things not available to userspace. */
#if (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__)

/**
 * @brief               The length of a process name.
 */
#define PROCESS_NAME_LENGTH \
                        (32)

/**
 * @brief               The length of a capability ID.
 */
#define CAPABILITY_CLASS_LENGTH \
                        (16)

/**
 * @brief               The length of a capability name.
 */
#define CAPABILITY_NAME_LENGTH \
                        (32)

/**
 * @brief               The length of a thread name.
 */
#define THREAD_NAME_LENGTH \
                        32

#endif /* (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__) */

/**
 * @brief               Different ways of halting.
 */
enum halt_t 
{
    /**
     * @brief           Reboot the machine. 
     */
    HALT_REBOOT,

    /**
     * @brief           Shut it down (with possible power-down as well). 
     */
    HALT_SHUTDOWN
};

/* System call numbers. */
enum system_call_t
{
    /* Lookup the providers for a service. */
    SYSTEM_CALL_SERVICE_LOOKUP,

    /* Connect to a service provider. */
    SYSTEM_CALL_SERVICE_CONNECT,

    /* Close a connection to a service. */
    SYSTEM_CALL_SERVICE_CLOSE,

    /* Invoke a function call to a service. */
    SYSTEM_CALL_SERVICE_INVOKE
};

/* Stupid, but just to get the AVL code compiling. FIXME: Remove this
   ASAP. */
#define malloc(n)       (NULL)
#define free(n)

#endif /* !__STORM_DEFINES_H__ */
