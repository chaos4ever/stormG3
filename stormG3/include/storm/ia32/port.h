/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Port in/output. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_PORT_H__
#define __STORM_IA32_PORT_H__

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

#endif /* !__STORM_IA32_PORT_H__ */
