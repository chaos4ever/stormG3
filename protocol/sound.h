/* $chaos: kernel.h,v 1.2 2002/12/02 20:49:28 per Exp $ */
/* Abstract: Definition of the sound protocol. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             sound.h
 * @brief            Definition of the sound protocol.
 */

#ifndef __PROTOCOL_SOUND_H__
#define __PROTOCOL_SOUND_H__

/**
 * @brief               The major version of the sound protocol. 
 */
#define SOUND_PROTOCOL_MAJOR_VERSION \
                        (0)

/**
 * @brief               The minor version of the sound protocol.
 */
#define SOUND_PROTOCOL_MINOR_VERSION \
                        (1)

/**
 * @brief               Sound functions. 
 */
enum sound_function_t
{
    boobaz
};

#endif /* !__PROTOCOL_SOUND_H__ */
