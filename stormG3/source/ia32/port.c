/* $chaos: port.c,v 1.3 2002/10/04 19:01:21 per Exp $ */
/* Abstract: I/O port management. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/ia32/port.h>

/* Linked list over allocated I/O regions. */
port_range_t *port_list = NULL;

/* Link in a port range into the list of allocated ports. */
static bool port_range_link (unsigned int start, unsigned int ports, 
                             const char *description)
{
    port_range_t *node = port_list;
    port_range_t *new_node;
    unsigned int end = start + ports;

    /* Check if the port range is already allocated. */
    while (node != NULL)
    {
        if ((start >= node->start &&
             start < (node->start + node->length)) ||
            (end >= node->start &&
             end < (node->start + node->length)) ||
            (start < node->start &&
             end >= (node->start + node->length)))
        {
            return FALSE;
        }    
    
        node = (port_range_t *) node->next;
    }

    /* OK, the requested region is free, we can open up the ports in the
       thread's I/O-map. But first, let's mark this region as used. */
    memory_global_allocate ((void **) &new_node, sizeof (port_range_t));

    new_node->start = start;
    new_node->length = ports;
    memory_global_allocate ((void **) &new_node->description,
                            string_length (description));
    string_copy (new_node->description, description);

    /* Add it to the list. */
    new_node->previous = NULL;
    new_node->next = (struct port_range_t *) port_list;

    if (port_list != NULL)
    {
        port_list->previous = (struct port_range_t *) new_node;
    }

    port_list = new_node;
    return TRUE;
}

/* Set up data structures for port allocation. */
void port_init (void)
{
    /* Allocate some reserved regions. FIXME: maybe a struct holding all the
       regions and a loop? */
    /* Interrupt controllers. */
    port_range_link (0x0020, 32, "Primary interrupt controller");
    port_range_link (0x00A0, 32, "Secondary interrupt controller");

    /* FPU. */
    port_range_link (0x00F8, 16, "Floating point unit");
}

/* Register a port range. */
return_t port_range_register (unsigned int start, unsigned int ports,
                                 char *description)
{
    /* Make sure we're not out of bounds. */
    if (start + ports > NUMBER_OF_PORTS)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    /* Try to add this port range into the list. */
    if (!port_range_link (start, ports, description))
    {
        return STORM_RETURN_BUSY;
    }

    return STORM_RETURN_SUCCESS;
}

/* Unregister a port range. */
return_t port_range_unregister (unsigned int start)
{
    port_range_t *port = port_list;

    while (port != NULL && port->start != start)
    {
        port = (port_range_t *) port->next;
    }

    /* Did we run out of the list? If so, this thread has not previously
       allocated a port range starting at this base, so just abort
       silently. */
    if (port == NULL)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    /* Unlink this entry from the list. First, check if it is the only
       entry. If so, everything gets very simple. */
    if (port->previous == NULL &&
        port->next == NULL)
    {
        port_list = NULL;
    }
    /* If it doesn't have a previous pointer, we can assume that this is
       the first entry. If so, make the next entry the start of the
       list. */
    else if (port->previous == NULL)
    {
        port_list = (port_range_t *) port->next;
    
        port_list->previous = NULL;
    }
    else if (port->next == NULL)
    {
        /* This entry is the last one. */
        port_range_t *previous = (port_range_t *) port->previous;
    
        previous->next = NULL;
    }
    else
    {
        /* We are in the middle of nowhere... umm, I mean, the list. */
        port_range_t *previous = (port_range_t *) port->previous;
        port_range_t *next = (port_range_t *) port->next;
    
        previous->next = (struct port_range_t *) next;
        next->previous = (struct port_range_t *) previous;
    }

    return STORM_RETURN_SUCCESS;
}
