/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Kernel log module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>

/* Return some information about the log service (function pointers to
   our functionality). */
static return_t service_info (void *info __attribute__ ((unused)))
{
    debug_print ("hej! piff puff\n");
    return STORM_RETURN_SUCCESS;
}

return_t module_start (void)
{
    service_register ("log", 1, (function_t) &service_info);
    return STORM_RETURN_SUCCESS;
}
