/* $chaos: log.c,v 1.2 2002/06/21 08:00:08 per Exp $ */
/* Abstract: Kernel log module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <log/log.h>

static char *log_urgency[] =
{
    "Emergency",
    "Error",
    "Warning",
    "Informative",
    "Debug"
};

/* Print something to the kernel log. */
static return_t log_print (unsigned int urgency __attribute__ ((unused)),
                           char *string)
{
    debug_print ("%s: %s\n", log_urgency[urgency], string);
    return STORM_RETURN_SUCCESS;
}

/* Return some information about the log service (function pointers to
   our functionality). */
static return_t service_info (log_service_t *log)
{
    log->magic_cookie = LOG_COOKIE;
    log->print = &log_print;
    return STORM_RETURN_SUCCESS;
}

return_t module_start (void)
{
    return service_register ("log", 1, (function_t) &service_info);
}
