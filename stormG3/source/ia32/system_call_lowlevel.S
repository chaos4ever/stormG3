/* $chaos: dotfile.emacs,v 1.37 2002/10/14 16:03:33 per Exp $ */
/* Abstract: Low-level system call. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

.globl system_call_lowlevel

/* This function is called whenever a system call is being done. */
system_call_lowlevel:
        pushal
        call system_call

        /* Simulate a pop of %EAX; it contains a return value that we
           don't wanna mess with. */
        addl    $4 * 0, %esp
        popl    %edi
        popl    %esi
        popl    %ebp

        /* ESP can't be popped for obvious reasons. */
        addl    $4, %esp
        popl    %ebx
        popl    %edx
        popl    %ecx
        iret
