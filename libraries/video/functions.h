/* $chaos: functions.h,v 1.2 2002/08/09 05:59:42 per Exp $ */
/* Abstract: Video library functions. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __VIDEO_FUNCTIONS_H__
#define __VIDEO_FUNCTIONS_H__

/* Lookup the first video service provider. */
extern return_t video_lookup (video_service_t *video);

/* Register a video service provider. */
extern return_t video_register (service_register_t *service_register_info,
                                service_method_t *service_method);
    
#endif /* !__VIDEO_FUNCTIONS_H__ */
