/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Time module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "time.h"

/* The log service provider that we are using. */
log_service_t log;

/* The current time & date. */
volatile unsigned int second, minute, hour, date, month, year;

/* The IRQ handler. */
static void irq_handler (unsigned int irq UNUSED)
{
    /* Read the time and date. */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_SECOND);
    second = port_uint8_in (RTC_DATA);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_MINUTE);
    minute = port_uint8_in (RTC_DATA);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_HOUR);
    hour = port_uint8_in (RTC_DATA);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_DATE);
    date = port_uint8_in (RTC_DATA);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_MONTH);
    month = port_uint8_in (RTC_DATA);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_YEAR);
    year = port_uint8_in (RTC_DATA);
    year += 2000;

    /* Read the C register. */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_C);
    port_uint8_in (RTC_DATA);

    debug_print ("%u-%u-%u %u:%u:%u\n", year, month, date, hour, minute,
                 second);
}

/* The entry point of the module. */
return_t module_start ()
{
    if (log_lookup (&log) != LOG_RETURN_SUCCESS)
    {
        return STORM_RETURN_NOT_FOUND;
    }

        /* Try to allocate the RTC's ports. */
    if (port_range_register (RTC_BASE, RTC_PORTS,"RTC") !=
        STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY,
                   "Could not allocate ports.");
        return STORM_RETURN_BUSY;
    }

    if (irq_register (RTC_IRQ, "RTC", &irq_handler) != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Could not allocate IRQ.");
        return STORM_RETURN_BUSY;
    }

    /* Enable the 1 Hz clock. */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_B);
    uint8_t b = port_uint8_in (RTC_DATA);
    BIT_SET(b, 4);
    debug_print ("%x\n", b);
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_B);
    port_uint8_out_pause (RTC_DATA, b);
    
    return STORM_RETURN_SUCCESS;
}
