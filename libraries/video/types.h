/* $chaos: types.h,v 1.1 2002/06/23 20:33:11 per Exp $ */
/* Abstract: Video library types. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LIBRARY_VIDOE_TYPES_H__
#define __LIBRARY_VIDEO_TYPES_H__

/* Function types. */
typedef return_t (*video_cursor_place_t)(int x, int y);

/* A log service. */
typedef struct
{
    /* The log magic cookie. */
    unsigned int magic_cookie;

    /* Function for placing the hardware cursor. */
    video_cursor_place_t cursor_place;
} video_service_t;

/* Initialization function. */
typedef return_t (*video_init_t)(video_service_t *);

#endif /* !__LIBRARY_VIDEO_TYPES_H__ */
