/* $chaos: dotfile.emacs,v 1.34 2002/09/30 13:33:00 per Exp $ */
/* Abstract: Exec library types. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __EXEC_TYPES_H__
#define __EXEC_TYPES_H__

typedef struct
{
    /* The block magic cookie. */
    unsigned int magic_cookie;

} exec_service_t;

#endif /* !__EXEC_TYPES_H__ */
