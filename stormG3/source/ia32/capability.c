/* $chaos: capability.c,v 1.4 2002/10/24 20:50:25 per Exp $ */
/* Abstract: Capabilities support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <storm/ia32/capability.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/memory.h>
#include <storm/ia32/process.h>
#include <storm/ia32/spinlock.h>
#include <storm/ia32/string.h>

/* Find out whether the given capability is in the list. Inner
   function for capability_has. */
static bool capability_find (capability_t *list,
                             const char *capability_class,
                             const char *capability_name)
{
    while (list != NULL)
    {
        if (string_compare (capability_class, list->class) == 0 &&
            string_compare (capability_name, list->name) == 0)
        {
            return TRUE;
        }

        list = (capability_t *) list->next;
    }

    return FALSE;
}

/* Has the current process the given capability. */
return_t capability_has (process_id_t process_id,
                         process_t *process_parameter,
                         const char *capability_class,
                         const char *capability_name, bool *result)
{
    process_t *process;
    
    if (process_parameter == NULL)
    {
        process = process_find (process_id);
    }
    else
    {
        process = process_parameter;
    }

    /* For bad code that doesn't check the return value, we start by
       making it FALSE. */
    *result = FALSE;

    if (process == NULL)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    /* Check input parameters. */
    if (capability_class == NULL || 
        capability_name == NULL)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    if (string_length (capability_class) > CAPABILITY_CLASS_LENGTH - 1 ||
        string_length (capability_name) > CAPABILITY_NAME_LENGTH - 1)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    *result = capability_find (process->capability_list,
                                   capability_class, capability_name);

    /* Fall back to class::super_user. */
    if (! *result)
    {
        *result = capability_find (process->capability_list,
                                   capability_class, CAPABILITY_SUPER_USER);
    }

    /* Fall back to kernel::super_user (global super-user
       capability). */    
    if (! *result)
    {
        *result = capability_find (process->capability_list,
                                   CAPABILITY_CLASS_KERNEL,
                                   CAPABILITY_SUPER_USER);
    }

    return STORM_RETURN_SUCCESS;
}

/* Add a capability to a process. */
return_t capability_add (process_id_t process_id,
                         process_t *process_parameter,
                         const char *capability_class,
                         const char *capability_name)
{
    process_t *process;
    
    if (process_parameter == NULL)
    {
        process = process_find (process_id);
    }
    else
    {
        process = process_parameter;
    }

    if (process == NULL)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    capability_t *capability_list = process->capability_list;
    capability_t *capability;

    /* Check the input. */
    if (capability_class == NULL ||
        capability_name == NULL)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    if (string_length (capability_class) > CAPABILITY_CLASS_LENGTH - 1 ||
        string_length (capability_name) > CAPABILITY_NAME_LENGTH - 1)
    {
        return STORM_RETURN_INVALID_ARGUMENT;
    }

    return_t return_value = memory_global_allocate ((void **) &capability, sizeof (capability_t));
    if (return_value != STORM_RETURN_SUCCESS)
    {
        return return_value;
    }

    string_copy (capability->class, capability_class);
    string_copy (capability->name, capability_name);
    capability->previous = (struct capability_t *) capability_list;
    capability->next = NULL;

    /* If we already have a list, add this capability to that list. */
    if (capability_list != NULL)
    {
        capability_list->next = (struct capability_t *) capability;
    }

    /* Okay, things are set up properly. Now go ahead and add it to
       the capability list that we have in the process. */
    spin_lock_interrupt (&process->lock);
    process->capability_list = capability;
    spin_unlock (&process->lock);

    return STORM_RETURN_NOT_IMPLEMENTED;
}
