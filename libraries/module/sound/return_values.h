/* $chaos: return_values.h,v 1.1 2002/10/04 20:53:22 per Exp $ */
/* Abstract: Return values used by the sound library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __SOUND_RETURN_VALUES_H__
#define __SOUND_RETURN_VALUES_H__

enum service_return_t
{
    /* The function returned successfully. */
    SOUND_RETURN_SUCCESS,

    /* No service was found. */
    SOUND_RETURN_SERVICE_UNAVAILABLE,
};

#endif /* !__SOUND_RETURN_VALUES_H__ */
