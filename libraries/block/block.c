/* $chaos: log.c,v 1.3 2002/07/04 21:25:44 per Exp $ */
/* Abstract: Block library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <block/block.h>

/* Resolve the first block service provider. FIXME: Should be able to
   return a list. */
return_t block_resolve (block_service_t *block)
{
    size_t services;
    service_t *service;

    /* Find the log service. */
    if (service_resolve ("block", NULL, NULL, NULL, 1, &services, &service) != STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to resolve block service provider.\n");
        return BLOCK_RETURN_SERVICE_UNAVAILABLE;
    }

    service[0].service_info (block);

    // FIXME: Free the memory allocated by service_resolve.

    return BLOCK_RETURN_SUCCESS;
}
