/* $chaos: return_values.h,v 1.1 2002/06/22 22:45:39 per Exp $ */
/* Abstract: Return values for unicode functions. */
/* Author: Anders Ohrt <doa@chaosdev.org> */

/* Copyright 2000-2002 chaos development */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LIBRARY_UNICODE_RETURN_VALUES_H__
#define __LIBRARY_UNICODE_RETURN_VALUES_H__

enum
{
    /* The function completed successfully. */
    UNICODE_RETURN_SUCCESS,
    
    /* The buffer was too small to hold the data. */
    UNICODE_RETURN_BUFFER_TOO_SHORT,
    
    /* Some UCS-2/4/UTF-8 character was invalid. */
    UNICODE_RETURN_UCS2_INVALID,
    UNICODE_RETURN_UCS4_INVALID,
    UNICODE_RETURN_UTF8_INVALID
};

#endif /* !__LIBRARY_UNICODE_RETURN_VALUES_H__ */
