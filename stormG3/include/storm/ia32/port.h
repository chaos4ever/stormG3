/* $chaos: port.h,v 1.1 2002/06/14 12:41:03 per Exp $ */
/* Abstract: Port in/output. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_PORT_H__
#define __STORM_IA32_PORT_H__

#include <storm/return_value.h>
#ifdef STORM
#include <storm/ia32/defines.h>
#include <storm/ia32/memory_global.h>
#include <storm/ia32/string.h>
#include <storm/ia32/types.h>
#endif /* STORM */

/* The total number of ports in the system. */
#define NUMBER_OF_PORTS                 65536

/* Type definitions. */
typedef struct
{
    unsigned int start;
    unsigned int length;
    // FIXME: Add this field.    module_id_t module_id;
    struct port_range_t *next;
    struct port_range_t *previous;
    char *description;
} port_range_t;


/* Inline functions. */
static inline void port_uint8_out (unsigned short port, unsigned char data)
{
    asm ("outb	%1,%0"
         :
         :
         "Nd"(port),
         "a"(data));
};

static inline unsigned char port_uint8_in (unsigned short port)
{
    unsigned char data;
    asm volatile ("inb	%1,%0"
                  :
                  "=a"(data)
                  :
                  "Nd"(port));

    return data;
};

/* Register a port range. */
extern return_t port_range_register (unsigned int base, unsigned int ports,
                                     char *description);

/* Unregister a port range. */
extern return_t port_range_unregister (unsigned int start);

#ifdef STORM

/* Initialize port allocation. */
extern void port_init (void);

#endif /* STORM */

#endif /* !__STORM_IA32_PORT_H__ */
