/* $chaos: boot.c,v 1.2 2002/10/24 22:15:57 per Exp $ */
/* Abstract: Boot program (somewhat like init in Unix systems). */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>

void _start (void) NORETURN;
int main (int argc UNUSED, char **argv UNUSED);

void _start (void)
{
   main (0, NULL);
   // syscall_exit (0);
   while (TRUE);
}

float q (float p);
float q (float p)
{
    p += 20;
    return p;
}

char *test = "spam spam spam!";

/* Main function. */
int main (int argc UNUSED, char **argv UNUSED)
{
    float p = 0;

    //    p = 1.5000902;
    //    p += 8.983293;
    q(p);
    asm("push test\n"
        "pushl $0x1\n"
        "int $0x88");
    // while (TRUE);
    return 0;
}
