/* $chaos: halt.h,v 1.3 2002/10/08 20:16:14 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file        halt.h
 * @brief       Functions for halting the machine. 
 */

#ifndef __STORM_IA32_HALT_H__
#define __STORM_IA32_HALT_H__

/**
 * @brief       Different ways of halting.
 */
enum halt_t {
    /**
     * @brief   Reboot the machine. 
     */
    HALT_REBOOT,

    /**
     * @brief   Shut it down (with possible power-down as well). 
     */
    HALT_SHUTDOWN
};

/**
 * @brief               Halt the machine. 
 * @param type          The halt type we want.
 * @return              It won't return. :-)
 */
extern return_t halt (enum halt_t type);

#endif /* !__STORM_IA32_HALT_H__ */
