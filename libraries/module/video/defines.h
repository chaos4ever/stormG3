/* $chaos: defines.h,v 1.2 2002/10/04 19:00:58 per Exp $ */
/* Abstract: Video library defines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __VIDEO_DEFINES_H__
#define __VIDEO_DEFINES_H__

/* The version of the video service. Increase when you make
   binary-incompatible changes. That way, all clients trying to
   connect to your service will fail. */
#define VIDEO_SERVICE_MAJOR_VERSION \
                        (0)

/* The minor version is used for handling dependencies when adding
   binary-compatible changes (like adding a new function). A program
   using the new function needs to have a new minor version to depend
   on. */
#define VIDEO_SERVICE_MINOR_VERSION \
                        (1)

#endif /* !__VIDEO_DEFINES_H__ */
