/* $chaos: dotfile.emacs,v 1.34 2002/09/30 13:33:00 per Exp $ */
/* Abstract: Boot program (somewhat like init in Unix systems). */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>

void _start (void);
int main (int argc UNUSED, char **argv UNUSED);

void _start (void)
{
    main (0, NULL);
    //    exit ();
}

/* Main function. */
int main (int argc UNUSED, char **argv UNUSED)
{
    while (TRUE);
}
