/* $chaos: log.c,v 1.2 2002/10/04 19:01:17 per Exp $ */
/* Abstract: Kernel log module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

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
static return_t service_info (void *log_void)
{
    log_service_t *log = (log_service_t *) log_void;
    log->magic_cookie = LOG_COOKIE;
    log->print = &log_print;
    log->print_formatted = &log_print_formatted;
    return STORM_RETURN_SUCCESS;
}

return_t module_start (void)
{
    // FIXME: Use log_register (bug #54)
    return service_register ("log", "chaos development", "Log module", "1", LOG_SERVICE_MAJOR_VERSION, LOG_SERVICE_MINOR_VERSION, &service_info);
}
