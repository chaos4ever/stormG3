/* $chaos: video.h,v 1.1 2002/12/03 14:45:42 johannes Exp $ */
/* Abstract: Video protocol defines. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             protocol/video.h
 * @brief            Definition of the video protocol.
 */

#ifndef __PROTOCOL_VIDEO_H__
#define __PROTOCOL_VIDEO_H__

/**
 * @brief               Video protocol major version.
 *
 * The version of the video service. Increase when you make
 * binary-incompatible changes. That way, all clients trying to
 * connect to your service will fail. 
 */
#define VIDEO_PROTOCOL_MAJOR_VERSION \
                        (0)

/**
 * @brief               Video protocol minor version.
 *
 * The minor version is used for handling dependencies when adding
 * binary-compatible changes (like adding a new function). A program
 * using the new function needs to have a new minor version to depend
 * on. 
 */
#define VIDEO_PROTOCOL_MINOR_VERSION \
                        (1)

/**
 * @brief               Video mode types.
 */
enum video_mode_t 
{
    /**
     * @brief           Text-based video modes.
     */
    VIDEO_MODE_TYPE_TEXT,

    /**
     * @brief           Graphical video modes.
     */
    VIDEO_MODE_TYPE_GRAPHIC,
};

#endif /* !__PROTCOL_VIDEO_H__ */
