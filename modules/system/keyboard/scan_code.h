/* $chaos: scan_code.h,v 1.1 2002/08/11 21:13:31 per Exp $ */
/* Abstract: Keyboard scan codes. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __SCAN_CODE_H__
#define __SCAN_CODE_H__

enum
{
  SCAN_CODE_ESCAPE              = 1,
  SCAN_CODE_BACK_SPACE          = 14,
  SCAN_CODE_TAB                 = 15,
  SCAN_CODE_ENTER               = 28,
  SCAN_CODE_LEFT_CONTROL        = 29,
  SCAN_CODE_LEFT_SHIFT          = 42,
  SCAN_CODE_RIGHT_SHIFT         = 54,
  SCAN_CODE_PRINT_SCREEN        = 55,
  SCAN_CODE_LEFT_ALT            = 56,
  SCAN_CODE_SPACE_BAR           = 57,      
  SCAN_CODE_CAPS_LOCK           = 58,
  SCAN_CODE_F1                  = 59,
  SCAN_CODE_F2                  = 60,
  SCAN_CODE_F3                  = 61,
  SCAN_CODE_F4                  = 62,
  SCAN_CODE_F5                  = 63,
  SCAN_CODE_F6                  = 64,
  SCAN_CODE_F7                  = 65,
  SCAN_CODE_F8                  = 66,
  SCAN_CODE_F9                  = 67,
  SCAN_CODE_F10                 = 68,
  SCAN_CODE_NUM_LOCK            = 69,
  SCAN_CODE_SCROLL_LOCK         = 70,
  SCAN_CODE_NUMERIC_7           = 71,
  SCAN_CODE_NUMERIC_8           = 72,
  SCAN_CODE_NUMERIC_9           = 73,
  SCAN_CODE_NUMERIC_MINUS       = 74,
  SCAN_CODE_NUMERIC_4           = 75,
  SCAN_CODE_NUMERIC_5           = 76,
  SCAN_CODE_NUMERIC_6           = 77,
  SCAN_CODE_NUMERIC_PLUS        = 78,
  SCAN_CODE_NUMERIC_1           = 79,
  SCAN_CODE_NUMERIC_2           = 80,
  SCAN_CODE_NUMERIC_3           = 81,
  SCAN_CODE_NUMERIC_0           = 82,
  SCAN_CODE_NUMERIC_DELETE      = 83,
  SCAN_CODE_PRINT_SCREEN2       = 84, /* Print Screen generates both
                                         55 and this. */
  SCAN_CODE_F11                 = 87,
  SCAN_CODE_F12                 = 88,

  /* We put in the 'Extended' (AT) keys here, even though they
     technically don't generate these scancodes. */
  SCAN_CODE_NUMERIC_ENTER       = 89,
  SCAN_CODE_RIGHT_CONTROL       = 90,
  SCAN_CODE_NUMERIC_SLASH       = 92,
  SCAN_CODE_RIGHT_ALT           = 94,
  SCAN_CODE_HOME                = 95,
  SCAN_CODE_UP                  = 96,
  SCAN_CODE_PAGE_UP             = 97,
  SCAN_CODE_LEFT                = 98,
  SCAN_CODE_RIGHT               = 99,
  SCAN_CODE_END                 = 100,
  SCAN_CODE_DOWN                = 101,
  SCAN_CODE_PAGE_DOWN           = 102,
  SCAN_CODE_INSERT              = 103,
  SCAN_CODE_DELETE              = 104,

  /* Windows keys. */
  SCAN_CODE_LEFT_WINDOWS        = 125,
  SCAN_CODE_RIGHT_WINDOWS       = 126,
  SCAN_CODE_MENU                = 127,
};

#endif /* !__SCANCODE_H__ */
