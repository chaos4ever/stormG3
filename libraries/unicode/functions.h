/* $chaos: functions.h,v 1.3 2002/05/23 11:14:39 per Exp $ */
/* Abstract: Function prototypes for the Unicode library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __LIBRARY_UNICODE_FUNCTIONS_H__
#define __LIBRARY_UNICODE_FUNCTIONS_H__

extern return_t unicode_ucs2_to_utf8_string
  (uint8_t *utf8_string, ucs2_t *ucs2_string, unsigned int max_utf8_bytes);

extern return_t unicode_ucs4_to_utf8_string
  (uint8_t *utf8_string, ucs4_t *ucs4_string, unsigned int max_utf8_bytes);

extern return_t unicode_utf8_to_ucs2_string
  (ucs2_t *ucs2_string, uint8_t *utf8_string, unsigned int max_ucs2_characters);

extern return_t unicode_utf8_to_ucs4_string
  (ucs4_t *ucs4_string, uint8_t *utf8_string, unsigned int max_ucs4_characters);

extern return_t unicode_ucs2_to_utf8 (uint8_t *utf8, ucs2_t ucs2);

extern return_t unicode_ucs4_to_utf8 (uint8_t *utf8, ucs4_t ucs4);

extern return_t unicode_utf8_to_ucs2 (ucs2_t *ucs2, uint8_t *utf8, 
                                      unsigned int *length);

extern return_t unicode_utf8_to_ucs4 (ucs4_t *ucs4, uint8_t *utf8,
                                      unsigned int *length);

extern unsigned int unicode_utf8_previous_character_length 
  (char *utf8_string, unsigned int string_position);

extern unsigned int unicode_utf8_next_character_length
  (char *utf8_string, unsigned int string_position);

extern unsigned int unicode_utf8_string_characters (uint8_t *utf8_string);

#endif /* !__LIBRARY_UNICODE_FUNCTIONS_H__ */
