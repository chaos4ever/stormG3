/* $chaos: log.c,v 1.3 2002/06/22 22:54:58 per Exp $ */
/* Abstract: Kernel log module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>
#include <log/log.h>

/* The version of log service that we provide. */
#define LOG_SERVICE_VERSION             1

static char *log_urgency[] =
{
    "Emergency",
    "Error",
    "Warning",
    "Informative",
    "Debug"
};

/* Print something to the kernel log. */
static return_t log_print (unsigned int urgency, char *string)
{
    debug_print ("%s: %s\n", log_urgency[urgency], string);
    return STORM_RETURN_SUCCESS;
}

/* Print something to the kernel log, in a more formatted fashion. */
static return_t log_print_formatted (unsigned int urgency, char *string, ...)
{
    // FIXME: Use the varargs as well.
    debug_print ("%s: %s\n", log_urgency[urgency], string);
    return STORM_RETURN_SUCCESS;
}

/* Return some information about the log service (function pointers to
   our functionality). */
static return_t service_info (log_service_t *log)
{
    log->magic_cookie = LOG_COOKIE;
    log->print = &log_print;
    log->print_formatted = &log_print_formatted;
    return STORM_RETURN_SUCCESS;
}

return_t module_start (void)
{
    return service_register ("log", LOG_SERVICE_VERSION, (function_t) &service_info);
}
