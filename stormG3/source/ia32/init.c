/* $chaos: init.c,v 1.4 2002/06/08 15:13:09 per Exp $ */
/* Abstract: storm initialization. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING.
   reference documentation. */

#include <storm/types.h>
#include <storm/ia32/defines.h>
#include <storm/ia32/gdt.h>
#include <storm/ia32/idt.h>
#include <storm/ia32/main.h>
#include <storm/ia32/multiboot.h>

/* FIXME: Move to another file. */
descriptor_t gdt[GDT_ENTRIES] __attribute__ ((section (".idt")));

/* The kernel stack. */
uint8_t kernel_stack[KERNEL_STACK_SIZE];

/* A temporary GDT that we copy into the real one. */
static uint16_t temporary_gdt[] = 
{
    /* Null descriptor. Generates GPF on access. */
    0x0000,
    0x0000,
    0x0000,
    0x0000,

    /* Kernel code segment (exec). */
    0xFFFF,
    0x0000,
    0x9800,
    0x00CF,

    /* Process data segment (read/write). */
    0xFFFF,
    0x0000,
    0x9200,
    0x00CF,
    
    /* Process code segment (exec). */
    0xFFFF,
    0x0000,
    0xF800,
    0x00CF,

    /* Process data segment (read/write). */
    0xFFFF,
    0x0000,
    0xF200,
    0x00CF
};

static uint16_t idtr[] UNUSED = 
{
    /* IDT limit. */
    IDT_SIZE - 1,
    0x0000,
    0x0000
};

static uint16_t gdtr[] UNUSED =
{ 
    /* GDT limit. */
    GDT_SIZE - 1,
    0x0000,
    0x0000
};

/* This is the first code of the kernel that gets executed. (well,
   almost. _start () sets up some stuff first...) */
static void kernel_entry (void)
{
    multiboot_init ();
    
    //  main (((u32 *) arguments_kernel)[0], (char **) arguments_kernel + 1);
    main_bootup (0, NULL);
    while (TRUE);
}

/* Multiboot header. */
static uint32_t multiboot_header[] __attribute__ ((section (".init.pre"), unused)) = 
{
    MULTIBOOT_MAGIC,
    MULTIBOOT_FLAGS,
    - (MULTIBOOT_MAGIC + MULTIBOOT_FLAGS)
};
                                     
/* This is the kernel entry point. */
void _start (void);
void _start (void)
{
    /* EBX contains the address to the multiboot table. Save this in
       the kernel data table. We can NOT use memory_copy here, since
       that will need a stack. */
    asm ("movl    %0, %%edi\n"
         "movl    %%ebx, %%esi\n"
         "movl    %1, %%ecx\n"
         "rep     movsl\n"
         :
         :
         "g" ((uint32_t) &multiboot_info),
         "g" (sizeof (multiboot_info_type) / 4));
  
    /* Move the GDT to the right location in memory. */
    asm ("cld\n"
         "movl    %0, %%edi\n"
         "movl    %1, %%esi\n"
         "movl    %2, %%ecx\n"
         "rep     movsl\n"
         "movl    %3, %%ecx\n"
         "movl    $0, %%eax\n"
         "rep     stosl"
         :
         : 
         "g" ((uint32_t) &gdt),
         "g" ((uint32_t) &temporary_gdt),
         "g" (sizeof (temporary_gdt) / 4),
         "g" ((GDT_SIZE - sizeof (temporary_gdt)) / 4));

    /* Clear the IDT. */
    asm ("movl    %0, %%edi\n"
         "movl    $0, %%eax\n"
         "movl    %1, %%ecx\n"
         "rep     stosl"
         :
         : 
         "g" (idt),
         "g" (IDT_SIZE / 4));
    
    /* IDT base. Couldn't do this in the declaration above since the
       compiler claimed it could not compute the address of idt. */
    idtr[1] = LOW_16 ((uint32_t) &idt);
    idtr[2] = HIGH_16 ((uint32_t) &idt);

        /* GDT base. */
    gdtr[1] = LOW_16 ((uint32_t) &gdt);
    gdtr[2] = HIGH_16 ((uint32_t) &gdt);

    /* Set up the GDTR and IDTR. */
    asm ("lgdt    gdtr\n"
         "lidt    idtr");

    /* Initialize the segment registers so they are loaded with our new
       selectors. */
    asm ("movl    %0, %%eax\n"
         "movw    %%ax, %%ss\n"
         "movl    %1, %%esp\n"
         "movw    %%ax, %%es\n"
         "movw    %%ax, %%fs\n"
         "movw    %%ax, %%gs\n"
         "movw    %%ax, %%ds"
         :
         :
         "g" (KERNEL_DATA_SELECTOR),
         "g" (&kernel_stack + KERNEL_STACK_SIZE));

    /* Pass control to the kernel. */
    asm ("ljmp   %0, %1"
         :
         :
         "n" (KERNEL_CODE_SELECTOR),
         "p" (&kernel_entry));
}

