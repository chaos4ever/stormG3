/* $chaos: console.h,v 1.2 2002/06/23 12:09:05 per Exp $ */
/* Abstract: Console module header file. */
/* Authors: Henrik Hallin <hal@chaosdev.org>
            Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <storm/storm.h>

/* The size of all mailboxes created by the console server. */
#define CONSOLE_MAILBOX_SIZE            1024

/* The default attribute to use for newly created consoles. */
#define CONSOLE_DEFAULT_ATTRIBUTE       0x07

/* The location of the physical video memory. */
#define CONSOLE_VIDEO_MEMORY            0xB8000
#define CONSOLE_VIDEO_MEMORY_SIZE       (32 * KB)

/* Maximum number of numeric arguments per escape sequence. */
#define MAX_NUMBER_OF_NUMERIC_PARAMETERS 10

/* Different types of consoles. */
enum
{
    CONSOLE_TYPE_TEXT,
    CONSOLE_TYPE_GRAPHIC
};

typedef struct
{
    uint8_t character;
    uint8_t attribute;
} __attribute__ ((packed)) character_t;

/* A console application structure. */
typedef struct
{
    /* Is this application listening for keyboard events? And how
       verbose should we be? */
    bool wants_keyboard;
    int keyboard_type;

    /* And/Or mouse? */
    bool wants_mouse;

    /* So we know where to send our stuff. */
    //    ipc_structure_type ipc_structure;

    /* Next application on this console. */
    struct console_application_t *next;
} console_application_t;

/* A virtual console structure. */
typedef struct
{
    /* Location of the cursor. */
    int cursor_x;
    int cursor_y;

    /* Stored location of the cursor. */
    int cursor_saved_x;
    int cursor_saved_y;

    /* If type is CONSOLE_TYPE_TEXT, characters. Otherwise, pixels. */
    int width;
    int height;  
    int depth;
    int type;

    /* The current state of the console. Used for ANSI escape
       sequences. */
    unsigned int state;
    unsigned int numeric_argument_index;
    int numeric_argument[MAX_NUMBER_OF_NUMERIC_PARAMETERS];

    /* FIXME: This should be extended to support other formats. Right
       now, we just use the EGA attribute. */
    uint8_t current_attribute;

    /* Pointer to the buffer for this console. */
    character_t *buffer;

    /* The actual output to this console should go here. When the
       console is activated, this and the previous one will differ. */
    character_t *output;

    /* FIXME: This isn't neccessary. */
    uint8_t modified_attribute;

    int character_width;
    int character_height;

    bool bold;
    bool underline;
    bool blink;
    bool inverse;

    /* The current application receives input events. (keyboard and
       mouse). */
    console_application_t *active_application;

    /* This linked list holds information about all the applications
       connected to this specific console. */
    console_application_t *application_list;

    /* Is this console locked? */
    /* FIXME: Real mutexing is needed. */
    bool lock;

    /* Next console. */
    struct console_t *next;
} console_t;

/* States for a console. */
enum
{
    CONSOLE_STATE_CHARACTER,
    CONSOLE_STATE_PREESCAPE,
    CONSOLE_STATE_ESCAPE,
    CONSOLE_STATE_NUMERIC,
};

/* Global variables. */
extern character_t *screen;
extern volatile bool has_video;
//extern ipc_structure_type video_structure;
extern volatile console_t *current_console;
extern volatile unsigned int number_of_consoles;
extern console_t *console_list;
extern volatile console_t *console_shortcut[];

/* External functions. */
//extern void handle_connection (mailbox_id_type reply_mailbox_id);
extern void console_link (console_t *console);
extern void console_flip (console_t *console);

#endif /* !__CONSOLE_H__ */
