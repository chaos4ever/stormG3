/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Video library return values. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __VIDEO_RETURN_VALUES_H__
#define __VIDEO_RETURN_VALUES_H__

enum
{
    /* The function executed successfully. */
    VIDEO_RETURN_SUCCESS,
    
    /* One of the arguments to a function was invalid in some way. */
    VIDEO_RETURN_INVALID_ARGUMENT,

    /* The video service could not be resolved. */
    VIDEO_RETURN_SERVICE_UNAVAILABLE,
};

#endif /* !__VIDEO_RETURN_VALUES_H__ */
