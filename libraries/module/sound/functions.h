/* $chaos: functions.h,v 1.2 2002/11/20 20:05:38 per Exp $ */
/* Abstract: Functions in the sound library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             sound/functions.h
 * @brief            Sound library.
 */

#ifndef __SOUND_FUNCTIONS_H__
#define __SOUND_FUNCTIONS_H__

/* Lookup the first sound service. */
extern return_t sound_lookup (sound_service_t *sound);

/* Register a sound service. */
extern return_t sound_register (service_register_t *service_register_info,
                                service_method_t *method);

#endif /* !__SOUND_FUNCTIONS_H__ */
