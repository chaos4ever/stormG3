/* $chaos: $ */
/* Abstract: Video protocol defines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             video.h
 * @brief            Definition of the video protocol.
 */

#ifndef __PROTOCOL_VIDEO_H__
#define __PROTOCOL_VIDEO_H__

/* The version of the video service. Increase when you make
   binary-incompatible changes. That way, all clients trying to
   connect to your service will fail. */
#define VIDEO_PROTOCOL_MAJOR_VERSION \
                        (0)

/* The minor version is used for handling dependencies when adding
   binary-compatible changes (like adding a new function). A program
   using the new function needs to have a new minor version to depend
   on. */
#define VIDEO_PROTOCOL_MINOR_VERSION \
                        (1)

#endif /* !__PROTCOL_VIDEO_H__ */
