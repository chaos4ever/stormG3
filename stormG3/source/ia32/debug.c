/* $chaos: debug.c,v 1.1 2002/05/25 20:09:40 per Exp $ */
/* Abstract: Code used for debugging the kernel. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING.
   reference documentation. */

#include <stdarg.h>
#include <storm/defines.h>
#include <storm/ia32/debug.h>
#include <storm/ia32/memory.h>

static uint32_t text_attribute = DEBUG_ATTRIBUTE_TEXT;
static uint32_t background_attribute = DEBUG_ATTRIBUTE_BACKGROUND;
static uint32_t volatile x_position = 0;
static uint32_t volatile y_position = 0;
debug_screen_type *screen = (debug_screen_type *) BASE_SCREEN;

/* Initialize debugging. */
void debug_init (void)
{
  /* Clear the screen. */
    memory_set_uint16 ((uint16_t *) screen, background_attribute * 256 + ' ',
                       DEBUG_SCREEN_WIDTH * DEBUG_SCREEN_HEIGHT *
                       sizeof (debug_screen_type));
}

/* Put a character at the given position. */
static inline void put_character (int x, int y, char character,
                                  int character_attribute)
{
  int index = (y * DEBUG_SCREEN_WIDTH) + x;

  screen[index].character = character;
  screen[index].attribute = character_attribute;
}

/* Basic printing function. */
static int print_simple (const char *string)
{
    uint32_t index;
    
    /* Handle the NULL string. */
    if (string == NULL)
    {
        print_simple ("(null)");
        return 0;
    }
    
    for (index = 0; string[index] != '\0'; index++)
    {
        put_character (x_position, y_position, string[index],
                       text_attribute);
        x_position++;
        
        if (x_position == DEBUG_SCREEN_WIDTH)
        {
            x_position = 0;
            y_position++;
            
            /* If we're passing the last line on screen, scroll everything
               upwards one line. */
            if (y_position >= DEBUG_SCREEN_HEIGHT)
            {
                y_position = DEBUG_SCREEN_HEIGHT - 1;
                memory_copy ((void *) screen, (void *) &screen[DEBUG_SCREEN_WIDTH],
                             (DEBUG_SCREEN_WIDTH * (DEBUG_SCREEN_HEIGHT - 1)) * 2);
                memory_set_uint16 ((void *) &screen[DEBUG_SCREEN_WIDTH *
                                                    (DEBUG_SCREEN_HEIGHT - 1)],
                                   background_attribute * 256 + ' ', DEBUG_SCREEN_WIDTH);
            }
        }
    }
    
    return index;
}

/* Convert a decimal number to a string. */
static void decimal_string (char *string, int number)
{
    int index = 0;
    const char decimal_character[] = "0123456789";
    char temp[11];
    int length;
    
    if (number == 0)
    {
        string[0] = '0';
        string[1] = '\0';
    }
    else
    {
        while (number != 0)
        {
            temp[index] = decimal_character[number % 10];
            number /= 10;
            index++;
        }
        
        length = index;
        
        for (index = 0; index < length; index++)
        {
            string[index] = temp[length - index - 1];
        }
        string[length] = 0;
    }
}

/* Convert a number to an hexadecimal string notation. Padded to eight
   digits with zeroes. */
static void hex_string (char *string, unsigned int number)
{
    int index;
    const char hex_character[] = "0123456789ABCDEF";
    
    for (index = 0; index < 8; index++)
    {
        /* Ugly solution? I don't know. Rewrite it cleaner if you can. */
        string[index] = hex_character[(number >> (4 * (7 - index))) % 16];
    }
    string[8] = 0;
}

/* Print a formatted string to screen. Only used for debugging. This
   is NOT a POSIX compliant function. */
void debug_print (const char *format_string, ...)
{
    va_list va_arguments;
    int index = 0;
    
    va_start (va_arguments, format_string);
    
    if (format_string == NULL)
    {
        print_simple ("debug_print: format_string == NULL.\n");
        return;
    }

    /* Main parser loop. */
    while (format_string[index] != 0)
    {
        switch (format_string[index])
        {
            /* Percent sign means we get a formatting code as the next
               character. */
            case '%':
            {
                index++;
                
                switch (format_string[index])
                {
                    /* Character. */
                    case 'c':
                    {
                        char character = va_arg (va_arguments, int);
                        
                        put_character (x_position, y_position, character,
                                       text_attribute);
                        
                        /* Move the cursor. */
                        x_position++;
                        
                        if (x_position >= DEBUG_SCREEN_WIDTH)
                        {
                            y_position++;
                            x_position = 0;
                        }
                        
                        break;
                    }
                    
                    /* String. */
                    case 's':
                    {
                        print_simple (va_arg (va_arguments, char *));
                        
                        break;
                    }
                    
                    /* Signed number. */
                    
                    case 'd':
                    {
                        char string[11];
                        signed number = va_arg (va_arguments, signed);
                        
                        /* If the number is negative, print it with a
                           hyphen before. */
                        if (number < 0)
                        {
                            string[0] = '-';
                            decimal_string (string + 1, -number);
                        }
                        else
                        {
                            decimal_string (string, number);
                        }
                        
                        print_simple (string);
                        break;
                    }
                    
                    /* Unsigned number. */
                    case 'u':
                    {
                        char string[11];
                        
                        decimal_string (string, 
                                        va_arg (va_arguments, unsigned));
                        print_simple (string);
                        
                        break;
                    }
                    
                    /* Hexadecimal number. Padded to eight characters
                       with zeroes. */
                    case 'p':
                    case 'x':
                    {
                        char string[9];
                        
                        hex_string (string, va_arg (va_arguments, unsigned));
                        print_simple (string);
                        
                        break;
                    }
                    
                    /* Anything other is printed out in plain. */
                    default:
                    {
                        put_character (x_position, y_position,
                                       format_string[index],
                                       text_attribute);
                        
                        /* Move the cursor. */
                        x_position++;
                        
                        if (x_position >= DEBUG_SCREEN_WIDTH)
                        {
                            y_position++;
                            x_position = 0;
                        }
                        
                        break;
                    }
                }
                break;
            }
            
            /* New line. */
            case '\n':
            {
                y_position++;
                x_position = 0; 
                
                break;
            }
            
            /* All regular characters are just printed out. */
            default:
            {
                put_character (x_position, y_position, format_string[index],
                               text_attribute);
                
                /* Move the cursor. */
                x_position++;
                
                if (x_position >= DEBUG_SCREEN_WIDTH)
                {
                    y_position++;
                    x_position = 0;
                }
            }
        }
        
        /* If we're passing the last line on screen, scroll everything
           upwards one line. */
        if (y_position == DEBUG_SCREEN_HEIGHT)
        {
            y_position--;
            memory_copy ((void *) screen, (void *) &screen[DEBUG_SCREEN_WIDTH],
                         (DEBUG_SCREEN_WIDTH * (DEBUG_SCREEN_HEIGHT - 1)) * 2);
            memory_set_uint16 ((void *) &screen[DEBUG_SCREEN_WIDTH *
                                                (DEBUG_SCREEN_HEIGHT - 1)],
                               background_attribute * 256 + ' ', 
                               DEBUG_SCREEN_WIDTH);
        }
        
        index++;
    }
    
    va_end (va_arguments);
}
