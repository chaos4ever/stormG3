/* $chaos: block.c,v 1.5 2002/10/28 07:56:33 per Exp $ */
/* Abstract: Block library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <block/block.h>

/* Lookup the first block service provider. */
// FIXME: Should be able to return a list.
return_t block_lookup (block_service_t *block)
{
    // FIXME: Support more than one block service. :-)
    size_t services = 1;
    service_t service;

    /* Find the block service. */
    if (service_lookup ("block", NULL, NULL, NULL, 
                        BLOCK_SERVICE_MAJOR_VERSION,
                        BLOCK_SERVICE_MINOR_VERSION, &services, &service) != 
        STORM_RETURN_SUCCESS)
    {
        debug_print ("Failed to lookup block service provider.\n");
        return BLOCK_RETURN_SERVICE_UNAVAILABLE;
    }

    service.service_info (block);

    // FIXME: Free the memory allocated by service_resolve.

    return BLOCK_RETURN_SUCCESS;
}
