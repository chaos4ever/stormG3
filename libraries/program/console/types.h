/* $chaos: types.h,v 1.1 2002/12/17 21:54:55 per Exp $ */
/* Abstract: Console library types. */
/* Author: Per Lundberg <per<@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LIBRARY_CONSOLE_TYPES_H__
#define __LIBRARY_CONSOLE_TYPES_H__

/**
 * @brief               A console ID. 
 */
typedef int console_id_t;

/**
 * @brief               A key event handler. 
 */
typedef return_t (*console_key_event_t)(keyboard_packet_t *keyboard_packet);

/**
 * @brief               Open a new console. 
 */
typedef return_t (*console_open_t)(console_id_t *console_id, 
                                   size_t width, size_t height,
                                   size_t depth, int mode_type);

/**
 * @brief               Close a console. 
 */
typedef return_t (*console_close_t)(console_id_t console_id);

/**
 * @brief               Output something to the console. 
 */
typedef return_t (*console_output_t)(console_id_t console_id, 
                                     const char *string);

/**
 * @brief               Move the cursor in a console.
 */
typedef return_t (*console_cursor_move_t)(console_id_t console_id, int x, int y);

/**
 * @brief               Print a formatted string.
 */
typedef return_t (*console_print_formatted_t)(console_id_t console_id, const char *format_string, ...);

/**
 * @brief               A console service. 
 */
typedef struct
{
    /**
     * @brief           The console magic cookie. 
     */
    unsigned int        magic_cookie;

    /**
     * @brief           The key event handler. 
     */
    console_key_event_t key_event;
    // mouse_event

    /**
     * @brief           Open a new console. 
     */
    console_open_t      open;

    /**
     * @brief           Close a previously opened console. 
     */
    console_close_t     close;

    /**
     * @brief           Send text to the console.
     */
    console_output_t    output;

    // TODO: console_input_t input (with and without blocking)

    /** 
     * @brief           Move the cursor in the console.
     */
    console_cursor_move_t 
                        cursor_move;

    /**
     * @brief           Print a formatted string.
     */
    console_print_formatted_t
                        print_formatted;
} console_service_t;

#endif /* !__LIBRARY_CONSOLE_TYPES_H__ */
