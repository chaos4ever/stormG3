/* $chaos: keyboard.h,v 1.3 2002/05/23 11:14:28 per Exp $ */
/* Abstract: Protocol used when communicating with keyboard
   servers. */
/* Authors: Per Lundberg <per@chaosdev.org>
            Henrik Hallin <hal@chaosdev.org> */

/* Copyright chaos development 1999-2002. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __KEYBOARD_KEYBOARD_H__
#define __KEYBOARD_KEYBOARD_H__

#include <storm/storm.h>

// FIXME: Have this be unique.
#define KEYBOARD_COOKIE                 0x12345678

/* "Special keys" are keys that don't generate printable UTF-8
   sequences (like F1, Escape etc). Note that in chaos, some keys that
   generate printable characters in other systems (for example Tab)
   are treated differently. */
enum
{
    KEYBOARD_SPECIAL_KEY_ESCAPE,
    KEYBOARD_SPECIAL_KEY_BACK_SPACE,
    KEYBOARD_SPECIAL_KEY_TAB,
    KEYBOARD_SPECIAL_KEY_ENTER,
    KEYBOARD_SPECIAL_KEY_CONTROL,
    KEYBOARD_SPECIAL_KEY_LEFT_SHIFT,
    KEYBOARD_SPECIAL_KEY_RIGHT_SHIFT,
    KEYBOARD_SPECIAL_KEY_PRINT_SCREEN,
    KEYBOARD_SPECIAL_KEY_ALT,
    KEYBOARD_SPECIAL_KEY_SPACE_BAR,
    KEYBOARD_SPECIAL_KEY_CAPS_LOCK,
    KEYBOARD_SPECIAL_KEY_F1,
    KEYBOARD_SPECIAL_KEY_F2,
    KEYBOARD_SPECIAL_KEY_F3,
    KEYBOARD_SPECIAL_KEY_F4,
    KEYBOARD_SPECIAL_KEY_F5, 
    KEYBOARD_SPECIAL_KEY_F6,
    KEYBOARD_SPECIAL_KEY_F7,
    KEYBOARD_SPECIAL_KEY_F8,
    KEYBOARD_SPECIAL_KEY_F9,
    KEYBOARD_SPECIAL_KEY_F10,
    KEYBOARD_SPECIAL_KEY_F11,
    KEYBOARD_SPECIAL_KEY_F12,
    KEYBOARD_SPECIAL_KEY_NUM_LOCK,
    KEYBOARD_SPECIAL_KEY_SCROLL_LOCK,
    KEYBOARD_SPECIAL_KEY_NUMERIC_7,
    KEYBOARD_SPECIAL_KEY_NUMERIC_8,
    KEYBOARD_SPECIAL_KEY_NUMERIC_9,
    KEYBOARD_SPECIAL_KEY_NUMERIC_MINUS,
    KEYBOARD_SPECIAL_KEY_NUMERIC_4,
    KEYBOARD_SPECIAL_KEY_NUMERIC_5,
    KEYBOARD_SPECIAL_KEY_NUMERIC_6,
    KEYBOARD_SPECIAL_KEY_NUMERIC_PLUS,
    KEYBOARD_SPECIAL_KEY_NUMERIC_1,
    KEYBOARD_SPECIAL_KEY_NUMERIC_2,
    KEYBOARD_SPECIAL_KEY_NUMERIC_3,
    KEYBOARD_SPECIAL_KEY_NUMERIC_0,
    KEYBOARD_SPECIAL_KEY_NUMERIC_DELETE,
    KEYBOARD_SPECIAL_KEY_LEFT_WINDOWS,
    KEYBOARD_SPECIAL_KEY_RIGHT_WINDOWS,
    KEYBOARD_SPECIAL_KEY_MENU
    
#if FALSE
    KEYBOARD_SPECIAL_KEY_HOME,
    KEYBOARD_SPECIAL_KEY_END,
    KEYBOARD_SPECIAL_KEY_INSERT
#endif
};

/* A keyboard packet is what gets sent whenever a key is pressed or
   released. */
typedef struct
{
    /* Does this packet contain a character code? If not, it is just
       one of the shift states that has been modified, or perhaps a
       'special key'. */
    bool has_character_code;
    
    /* Is this a special key? */
    bool has_special_key;
    
    /* Was the key pressed or released? */
    bool key_pressed;
    
    /* The shift states. */
    bool left_shift_down;
    bool right_shift_down;
    bool left_alt_down;
    bool right_alt_down;
    bool left_control_down;
    bool right_control_down;
    bool left_windows_down;
    bool right_windows_down;
    bool task_list_down;
    
    /* If has_special_key is TRUE, this field contains the key code
       for this key. */
    uint32_t special_key;

    /* Six bytes for the character code, encoded with UTF-8. */
    uint8_t character_code[6];
} keyboard_packet_t;

#endif /* !__KEYBOARD_KEYBOARD_H__ */
