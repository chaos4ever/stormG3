/* $chaos: timer.c,v 1.1 2002/06/18 19:42:00 per Exp $ */
/* Abstract: Timer support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/ia32/bit.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/dispatch.h>
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

    /* Channel 2. We use this to get a good timer. (How?) */
    port_uint8_out (PIT_MODE_PORT, (COUNTER_2_SELECT | ACCESS_LOW_COUNTER_U8 |
                                    ACCESS_HIGH_COUNTER_U8 | MODE_3_SELECT |
                                    BINARY_COUNTER));
    port_uint8_out (PIT_COUNTER_2, LOW_8 (COUNTER_DIVISOR (1000)));
    port_uint8_out (PIT_COUNTER_2, HIGH_8 (COUNTER_DIVISOR (1000)));
}

/* Sleep the given amount of milliseconds (by looping). */
return_t timer_sleep_milli (unsigned int time)
{
    /* The multiplication factor that we need to do when checking ticks. */
    unsigned int factor = 1000 / hz;
    unsigned int start = ticks * factor;

    // FIXME: Do a hlt if IF is set. int $0x20 will ruin the timekeeping...
    while (ticks * factor < start + time);

    return STORM_RETURN_SUCCESS;
}
