/* $chaos: keyboard.h,v 1.1 2002/08/11 21:13:31 per Exp $ */
/* Abstract: Header file for the keyboard module. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 1998-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <console/console.h>
#include <keyboard/keyboard.h>
#include <log/log.h>

/* Version of the service. */
#define KEYBOARD_SERVICE_VERSION                1

/* Timeout in ms for keyboard command acknowledge. */
#define KEYBOARD_TIMEOUT                        1000

/* Timeout in ms for initializing the keyboard. */
#define KEYBOARD_INIT_TIMEOUT                   1000

/* Keyboard commands. */
#define KEYBOARD_COMMAND_SET_LEDS               0xED
#define KEYBOARD_COMMAND_SET_RATE               0xF3
#define KEYBOARD_COMMAND_ENABLE                 0xF4
#define KEYBOARD_COMMAND_DISABLE                0xF5
#define KEYBOARD_COMMAND_RESET                  0xFF

/* Keyboard replies. */
/* Power on reset. */
#define KEYBOARD_REPLY_POWER_ON_RESET           0xAA

/* Acknowledgement of previous command. */
#define KEYBOARD_REPLY_ACK                      0xFA

/* Command NACK, send the command again. */
#define KEYBOARD_REPLY_RESEND                   0xFE

/* Hardware defines. */
#define KEYBOARD_IRQ                            1

/* Return values from keyboard_read_data (). */
/* No data. */
#define KEYBOARD_NO_DATA                        (-1)

/* Parity or other error. */
#define KEYBOARD_BAD_DATA                       (-2)

/* Shift states. */
#define KEYBOARD_LEFT_SHIFT                     (1 << 0)
#define KEYBOARD_RIGHT_SHIFT                    (1 << 1)
#define KEYBOARD_LEFT_ALT                       (1 << 2)
#define KEYBOARD_RIGHT_ALT                      (1 << 3)
#define KEYBOARD_LEFT_CONTROL                   (1 << 4)
#define KEYBOARD_RIGHT_CONTROL                  (1 << 5)

/* Function prototypes. */
extern void keyboard_clear_input(void);
extern const char *keyboard_set_repeat_rate (void);
extern void keyboard_handle_event (uint8_t scancode);
extern const char *keyboard_init (void);
extern void keyboard_update_leds (void);
extern void keyboard_irq_handler (unsigned int irq);
extern bool keyboard_main (void);

/* The log service we are using. */
extern log_service_t log;

/* The keyboard event handler that we are using. */
extern console_key_event_t key_event;

#endif /* !__KEYBOARD_H__ */
