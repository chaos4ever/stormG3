/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: CPU initialization code. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/ia32/cpu.h>
#include <storm/ia32/memory.h>

cpu_info_t cpu_info;

/* If CPUID is not supported, we don't bother to set a CPU name. */
static const char *cpu_name_nocpuid = "Noname";
static char cpuid_string[13];

/* Generic CPUID function */
static inline void cpuid (uint32_t command, uint32_t *eax, uint32_t *ebx,
                          uint32_t *ecx, uint32_t *edx)
{
    asm volatile ("cpuid"
                  : "=a" (*eax), "=b" (*ebx), "=c" (*ecx), "=d" (*edx)
                  : "a" (command)
                  : "cc");
}

/* Check if the CPUID instruction is available on this system.  This
   is distinguished by checking if CPU_FLAG_ID in eflags can be
   toggled. If that's true, the CPU has the CPUID instruction. See
   Intel's documentation for more information about how the CPUID
   instruction works. */
static int has_cpuid (void)
{
    int return_value;
    
    asm volatile ("pushl       %%ebx\n"
                  
                  /* Invert id bit. */
                  "pushfl\n"
                  "xorl        %1, (%%esp)\n"
                  "popfl\n"
                  
                  /* Read eflags register and mask all bits but id bit. */
                  "pushfl\n"
                  "movl        (%%esp), %%eax\n"
                  "andl        %1, %%eax\n"
                  "popfl\n"
                  
                  /* Invert id bit. */
                  "pushfl\n"
                  "xorl        %1, (%%esp)\n"
                  "popfl\n"
                  
                  /* Mask. */
                  "pushfl\n"
                  "movl        (%%esp), %%ebx\n"
                  "andl        %1, %%ebx\n"
                  "popfl\n"
                  
                  /* Is id bit the same? */
                  "cmpl        %%ebx, %%eax\n"
                  "jne         1f\n"
                  
                  /* CPUID not supported. */
                  "movl        $0, %%eax\n"
                  "jmp         2f\n"
                  "1: movl     $1, %%eax\n"
                  "2: popl     %%ebx\n"
                  : "=&a" (return_value)
                  : "g" (CPU_FLAG_ID));
    
    return return_value;
}

/* Check if the current CPU is a 486. Returns 1 if 486 and zero if
   386. */
static int is_486 (void)
{
    int return_value;
    
    asm ("pushl   %%ecx\n"
    
         "pushfl\n"
         "popl    %%eax\n"
         "movl    %%eax, %%ecx\n"
         "xorl    $0x40000, %%eax\n"
         "pushl   %%eax\n"
         "popf\n"
                  
         "pushf\n"
         "popl    %%eax\n"
         "xorl    %%ecx, %%eax\n"
         "and     $0x40000, %%eax\n"
         "je      1f\n"
  
         /* 486 was detected. */
         "movl   $1, %%eax\n"
         "jmp    2f\n"
                
         "1:  movl $0, %%eax\n"
         "2:  popl   %%ecx"
         : "=&a" (return_value));
    
    return return_value;
}

/* Initialize the CPU. */
void cpu_init (void)
{
    memory_set_uint8 ((uint8_t *) &cpu_info, 0, sizeof (cpu_info_t));
    /* If CPUID is available, use it. */
    if (has_cpuid ())
    {
        uint32_t dummy;
        cpu_info.cpuid = 1;

        /* Get CPU vendor name. */
        cpuid (CPUID_GET_CPU_VENDOR, &dummy, (uint32_t *) &cpuid_string[0],
               (uint32_t *) &cpuid_string[8], (uint32_t *) &cpuid_string[4]);
        
        cpu_info.name = cpuid_string;
        
        /* Get model type and flags. */
        cpuid (CPUID_GET_CPU_INFO, (uint32_t *) &cpu_info.signature, &dummy,
               &dummy, (uint32_t *) &cpu_info.flags.flags);
    }
    else
    {
        cpu_info.name = cpu_name_nocpuid;
        cpu_info.cpuid = 0;
        
        /* Now detect if the CPU is a 386 or 486. */
        if (is_486 ())
        {
            cpu_info.family = 4;
        }
        else
        {
            cpu_info.family = 3;
        }
    }

    /* We don't resolve model/family/stepping into CPU names; that is
       done on library level to keep the kernel bloat down. */
}

