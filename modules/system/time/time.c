/* $chaos: time.c,v 1.2 2002/08/15 22:21:16 per Exp $ */
/* Abstract: Time module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include "time.h"

/* The log service provider that we are using. */
log_service_t log;

/* 'chaos time' -- similar to UNIX time, but with a 64-bit time_t. */
static time_t time = 0;
static time_t uptime = 0;

/* The current time & date. */
volatile unsigned int second, minute, hour, date, month, year, century;

extern void irq_handler (unsigned int irq UNUSED);

/* The IRQ handler. */
void irq_handler (unsigned int irq UNUSED)
{
    // FIXME: Should we just read the time once and convert it into
    // chaos time, and never more use the CMOS time, or what?

    /* Read the time and date. We don't set binary mode, since it's
       broken or buggy on many machines. */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_SECOND);
    // FIXME: This should not be needed.
    second = port_uint8_in (RTC_DATA);
    second = BCD_TO_DECIMAL (second);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_MINUTE);
    minute = port_uint8_in (RTC_DATA);
    minute = BCD_TO_DECIMAL (minute);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_HOUR);
    hour = port_uint8_in (RTC_DATA);
    hour = BCD_TO_DECIMAL (hour);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_DATE);
    date = port_uint8_in (RTC_DATA);
    date = BCD_TO_DECIMAL (date);

    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_MONTH);
    month = port_uint8_in (RTC_DATA);
    month = BCD_TO_DECIMAL (month);

    /* Weird, but the year is not BCD-coded... Blame Intel, IBM or
       whoever. */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_YEAR);
    year = port_uint8_in (RTC_DATA);

    /* We could skip this and just add 2000, but it would be lame and
       would break at next century change. :-) */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_CENTURY);
    century = port_uint8_in (RTC_DATA);
    century = BCD_TO_DECIMAL (century);

    year += century * 100;

    /* Increase our time pointer as well. */
    time++;
    uptime++;

    /* Read the C register. */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_C);
    port_uint8_in (RTC_DATA);
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

    /* Do this before we enable the interrupt so we won't miss any
       interrupts. */
    if (irq_register (RTC_IRQ, "RTC", &irq_handler) != STORM_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY, "Could not allocate IRQ.");
        return STORM_RETURN_BUSY;
    }

    /* We have the hardware. Now, read the current time and update
       time. FIXME: Do this. */

    /* Enable the 1 Hz clock. */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_B);
    uint8_t b = 0;
    BIT_SET(b, 4); /* One interrupt each second. */
    BIT_SET(b, 1); /* 24hr format (otherwise we can't distinguish). */
    port_uint8_out_pause (RTC_COMMAND, RTC_REGISTER_B);
    port_uint8_out_pause (RTC_DATA, b);

    // FIXME: Register a service as well. (bug #24)    
    return STORM_RETURN_SUCCESS;
}
