/* $chaos: types.h,v 1.2 2002/07/10 21:55:19 per Exp $ */
/* Abstract: Console library types. */
/* Author: Per Lundberg <per<@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __CONSOLE_TYPES_H__
#define __CONSOLE_TYPES_H__

/* A console ID. */
typedef int console_id_t;

/* A key event handler. */
typedef return_t (*console_key_event_t)(keyboard_packet_t *keyboard_packet);

/* Open a new console. */
typedef return_t (*console_open_t)(console_id_t *console_id, 
                                   size_t width, size_t height,
                                   size_t depth, int mode_type);

/* Close a console. */
typedef return_t (*console_close_t)(console_id_t console_id);

/* Output something to the console. */
typedef return_t (*console_output_t)(console_id_t console_id, 
                                     const char *string);

/* A console service. */
typedef struct
{
    /* The console magic cookie. */
    unsigned int magic_cookie;

    /* The key event handler. */
    console_key_event_t key_event;
    // mouse_event

    /* A function for opening a new console. */
    console_open_t open;

    /* A function for closing a previously opened console. */
    console_close_t close;

    /* A function for outputting to this console. */
    console_output_t output;

    // TODO: console_input_t input (with and without blocking)
} console_service_t;

/* Initialization function. */
typedef return_t (*console_init_t)(console_service_t *);

#endif /* !__CONSOLE_TYPES_H__ */
