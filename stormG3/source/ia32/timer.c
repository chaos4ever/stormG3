/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Timer support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/ia32/bit.h>
#include <storm/ia32/port.h>
#include <storm/ia32/timer.h>

/* The timer frequency. */
unsigned int hz = 100;

/* Initialise PIT channels 0. */
void timer_init (void)
{
    /* Channel 0. */
    port_uint8_out (PIT_MODE_PORT, (COUNTER_0_SELECT | ACCESS_LOW_COUNTER_U8 |
                                    ACCESS_HIGH_COUNTER_U8 | MODE_3_SELECT |
                                    BINARY_COUNTER));

    /* LSB first, then MSB. */
    port_uint8_out (PIT_COUNTER_DIVISOR, LOW_8 (COUNTER_DIVISOR (hz)));
    port_uint8_out (PIT_COUNTER_DIVISOR, HIGH_8 (COUNTER_DIVISOR (hz)));
}
