/* $chaos: dotfile.emacs,v 1.34 2002/09/30 13:33:00 per Exp $ */
/* Abstract: Return values used by the exec library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __EXEC_RETURN_VALUES_H__
#define __EXEC_RETURN_VALUES_H__

enum
{
    /* The function returned successfully. */
    EXEC_RETURN_SUCCESS,

    /* No exec service provider was found. */
    EXEC_RETURN_SERVICE_UNAVAILABLE,
};

#endif /* !__EXEC_RETURN_VALUES_H__ */
