/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Virtual file system provider. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>

int module_start (void)
{
    //    return service_register ("filesystem", "chaos development", "Minix module",
    //                             "1", FILESYSTEM_SERVICE_VERSION, &service_info);
    //    return service_register (
    return STORM_RETURN_SUCCESS;
}
