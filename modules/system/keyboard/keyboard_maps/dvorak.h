/* $chaos: dvorak.h,v 1.3 2002/06/18 09:37:50 per Exp $ */
/* Abstract: A dvorak translation table for chaos. This probably
   needs some fixup before it is usable. */
/* Author: Andreas Zetterlund <metal_leif@lycos.com> */

/* Copyright 2000-2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __DVORAK_H__
#define __DVORAK_H__

const char *dvorak_keyboard_map[] =
{
  NULL, NULL, "1",  "2",  "3",  "4",  "5",  "6",
  "7",  "8",  "9",  "0",  "[",  "]",  NULL, NULL,
  "'",  ",",  ".",  "p",  "y",  "f",  "g",  "c",
  "r",  "l",  "/",  "=",  NULL, NULL, "a",  "o",
  "e",  "u",  "i",  "b",  "h",  "t",  "n",  "s",
  "-",  "\\", NULL, "<",  ";",  "q",  "j",  "k",
  "x",  "b",  "m",  "w",  "v",  "z",  NULL, "*",
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, "-",  NULL, NULL, NULL, "+",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, "<",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

const char *dvorak_keyboard_map_shift[] =
{
  NULL, NULL, "!",  "@",  "#",  "$",  "%",  "^",
  "&",  "*",  "(",  ")",  "{",  "}",  NULL, NULL,
  "\"", "<",  ">",  "P",  "Y",  "F",  "G",  "C",
  "R",  "L",  "?",  "+",  NULL, NULL, "A",  "O",
  "E",  "U",  "I",  "D",  "H", "T",   "N",  "S",
  "_",  "|",  NULL, ">",  ":", "Q",   "J",  "K",
  "X",  "B",  "M",  "W",  "V",  "Z",  NULL, "*",
  NULL, " ",  NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, "-",  NULL, NULL, NULL, "+",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, ">",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

const char *dvorak_keyboard_map_altgr[] =
{
  NULL, NULL, NULL, "@",  "£",  "$",  NULL, NULL,
  "{",  "[",  "]",  "}",  "\\", NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, "~",  NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, " ",  NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, "|",  NULL,
  NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
  NULL
};

#endif /* !__DVORAK_H__ */
