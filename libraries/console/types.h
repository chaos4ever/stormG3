/* $chaos: types.h,v 1.3 2002/05/23 11:14:26 per Exp $ */
/* Abstract: Console library types. */
/* Author: Per Lundberg <per<@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __CONSOLE_TYPES_H__
#define __CONSOLE_TYPES_H__

/* A key event handler. */
typedef return_t (*console_key_event_t)(keyboard_packet_t *keyboard_packet);

/* A console service. */
typedef struct
{
    /* The console magic cookie. */
    unsigned int magic_cookie;

    /* The key event handler. */
    console_key_event_t key_event;
    // mouse_event
} console_service_t;

/* Initialization function. */
typedef return_t (*console_init_t)(console_service_t *);

#endif /* !__CONSOLE_TYPES_H__ */
