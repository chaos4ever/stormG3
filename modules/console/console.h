/* $chaos: console.h,v 1.3 2002/06/23 20:37:02 per Exp $ */
/* Abstract: Console module header file. */
/* Authors: Henrik Hallin <hal@chaosdev.org>
            Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <storm/storm.h>
#include <video/video.h>

/* The default attribute to use for newly created consoles. */
#define CONSOLE_DEFAULT_ATTRIBUTE       0x07

/* The location of the physical video memory. */
#define CONSOLE_VIDEO_MEMORY            0xB8000
#define CONSOLE_VIDEO_MEMORY_SIZE       (32 * KB)

/* Maximum number of numeric arguments per escape sequence. */
#define MAX_NUMBER_OF_NUMERIC_PARAMETERS 10

/* Default width/height/depth. */
#define CONSOLE_DEFAULT_WIDTH           80
#define CONSOLE_DEFAULT_HEIGHT          25
#define CONSOLE_DEFAULT_DEPTH           0

typedef struct
{
    uint8_t character;
    uint8_t attribute;
} __attribute__ ((packed)) character_t;

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
extern volatile console_t *current_console;
extern volatile unsigned int number_of_consoles;
extern console_t *console_list;
extern volatile console_t *console_shortcut[];
extern video_service_t video;

/* External functions. */
extern void console_link (console_t *console);
extern void console_flip (console_t *console);
extern void console_kill_screen (console_t *console, int argument);
extern void console_cursor_move (console_t *console, int x, int y);

#endif /* !__CONSOLE_H__ */
