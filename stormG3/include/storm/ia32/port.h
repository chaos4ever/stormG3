/* $chaos: port.h,v 1.8 2002/10/22 19:37:41 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                port.h
 * @brief               Port in/output. 
 */

#ifndef __STORM_IA32_PORT_H__
#define __STORM_IA32_PORT_H__

#include <storm/ia32/types.h>

/* Inline functions. */
static inline void port_uint8_out (unsigned short port, uint8_t data)
{
    asm ("outb	%1,%0"
         :
         :
         "Nd"(port),
         "a"(data));
};

static inline uint8_t port_uint8_in (unsigned short port)
{
    unsigned char data;
    asm volatile ("inb	%1,%0"
                  :
                  "=a"(data)
                  :
                  "Nd"(port));

    return data;
};

/* 'Pausing' version of the above. */
static inline void port_uint8_out_pause (uint16_t port, uint8_t data)
{
    asm ("outb %1, %0\n"
         "jmp 1f\n"
         "1: jmp 2f\n"
         "2:"
         :
         :
         "Nd" (port),
         "a" (data));
}

static inline void port_uint16_out_pause (uint16_t port, uint16_t data)
{
    asm ("outw %1, %0\n"
         "jmp 1f\n"
         "1: jmp 2f\n"
         "2:"
         :
         : 
         "Nd" (port),
         "a" (data));
}

static inline void port_uint32_out_pause (uint16_t port, uint32_t data)
{
    asm ("outl %1, %0\n"
         "jmp 1f\n"
         "1: jmp 2f\n"
         "2:"
         :
         :
         "Nd" (port),
         "a" (data));
}

/* String operations. */
static inline void port_uint8_out_string (uint16_t port, uint8_t *data,
                                          size_t length)
{
    asm volatile ("cld\n"
                  "rep\n"
                  "outsb"
                  :
                  :
                  "c" (length),
                  "S" (data),
                  "d" (port));
}

static inline void port_uint32_out_string (uint16_t port, uint32_t *data,
                                           size_t length)
{
    asm volatile ("cld\n"
                  "rep\n"
                  "outsl"
                  :
                  :
                  "c" (length),
                  "S" (data),
                  "d" (port));
}

/* The rest is only for the kernel and its modules. */
#if (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__)

#include <storm/return_value.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/string.h>

/**
 * @brief The total number of ports in the system. 
 */
#define NUMBER_OF_PORTS                 65536

/** 
 * @brief               A port range. 
 */
typedef struct
{
    unsigned int        start;
    unsigned int        length;
    // FIXME: Add this field.    module_id_t module_id;
    struct port_range_t *next;
    struct port_range_t *previous;
    char                *description;
} port_range_t;

/**
 * @brief               Initialize port allocation. 
 */
extern void port_init (void);

#endif /* (defined __STORM_KERNEL__) || (defined __STORM_KERNEL_MODULE__) */

#endif /* !__STORM_IA32_PORT_H__ */
