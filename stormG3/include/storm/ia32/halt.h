/* $chaos: halt.h,v 1.1 2002/08/11 18:39:03 per Exp $ */
/* Abstract: Functions for halting the machine. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_HALT_H__
#define __STORM_IA32_HALT_H__

enum halt_t {
    /* Reboot the machine. */
    HALT_REBOOT,

    /* Shut it down (with possible power-down as well). */
    HALT_SHUTDOWN
};

/* Halt the machine. */
extern return_t halt (enum halt_t type);

#endif /* !__STORM_IA32_HALT_H__ */
