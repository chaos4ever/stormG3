/* $chaos: return_values.h,v 1.1 2002/06/23 20:33:12 per Exp $ */
/* Abstract: String library return values. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LIBRARY_STRING_RETURN_VALUES_H__
#define __LIBRARY_STRING_RETURN_VALUES_H__

enum
{
    /* The function completed successfully. */
    STRING_RETURN_SUCCESS,
  
    /* One or more of the arguments to a function was invalid. */
    STRING_RETURN_INVALID_ARGUMENT,
};

#endif /* !__LIBRARY_STRING_RETURN_VALUES_H__ */
