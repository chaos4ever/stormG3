/* $chaos: swedish.h,v 1.3 2002/08/20 06:36:25 per Exp $ */
/* Abstract: A swedish keyboard translation map for chaos. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 1998-2000 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __KEYBOARD_MAPS_SWEDISH_H__
#define __KEYBOARD_MAPS_SWEDISH_H__

const char *swedish_keyboard_map[] =
{
  NULL, NULL, "1",  "2",  "3",  "4",  "5",  "6",
  "7",  "8",  "9",  "0",  "+",  NULL,  NULL, NULL,
  "q",  "w",  "e",  "r",  "t",  "y",  "u",  "i",
  "o",  "p",  "å",  NULL, NULL, NULL, "a",  "s",
  "d",  "f",  "g",  "h",  "j",  "k",  "l",  "ö",
  "ä",  "§",  NULL, "'",  "z",  "x",  "c",  "v",
  "b",  "n",  "m",  ",",  ".",  "-",  NULL, "*",
  NULL, " ",  NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, "-",  NULL, NULL, NULL, "+",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, "<",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

const char *swedish_keyboard_map_upper[] =
{
  NULL, NULL, "1",  "2",  "3",  "4",  "5",  "6",
  "7",  "8",  "9",  "0",  "+",  NULL,  NULL, NULL,
  "Q",  "W",  "E",  "R",  "T",  "Y",  "U",  "I",
  "O",  "P",  "Å",  NULL, NULL, NULL, "A",  "S",
  "D",  "F",  "G",  "H",  "J",  "K",  "L",  "Ö",
  "Ä",  "§",  NULL, "'",  "Z",  "X",  "C",  "V",
  "B",  "N",  "M",  ",",  ".",  "-",  NULL, "*",
  NULL, " ",  NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, "-",  NULL, NULL, NULL, "+",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, "<",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

const char *swedish_keyboard_map_shift[] =
{
  NULL, NULL, "!",  "\"", "#",  "$",  "%",  "&",
  "/",  "(",  ")",  "=",  "?",  "`",  NULL, NULL,
  "Q",  "W",  "E",  "R",  "T",  "Y",  "U",  "I",
  "O",  "P",  "Å",  "^",  NULL, NULL, "A",  "S",
  "D",  "F",  "G",  "H",  "J",  "K",  "L",  "Ö",
  "Ä",  "½",  NULL, "*",  "Z",  "X",  "C",  "V",
  "B",  "N",  "M",  ";",  ":",  "_",  NULL, "*",
  NULL, " ",  NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, "-",  NULL, NULL, NULL, "+",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, ">",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

const char *swedish_keyboard_map_altgr[] =
{
  NULL, NULL, NULL, "@",  NULL, "$",  NULL, NULL,
  "{",  "[",  "]",  "}",  "\\", NULL, NULL, NULL,
  NULL, NULL, "�",  NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, "~",  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, "¢",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, " ",  NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, "|",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

#endif /* !__KEYBOARD_MAPS_SWEDISH_H__ */
