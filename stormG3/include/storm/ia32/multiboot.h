/* $chaos: multiboot.h,v 1.1 2002/05/25 20:09:39 per Exp $ */
/* Abstract: Multiboot stuff. */
/* Author: Per Lundberg <per@chaosdev.org> 
           Henrik Hallin <hal@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_MULTIBOOT_H__
#define __STORM_IA32_MULTIBOOT_H__

#include <storm/types.h>
#include <storm/ia32/bit.h>

/* Enumerations. */
enum
{
    /* Indicates that the boot loader should page align modules. */
    MULTIBOOT_PAGE_ALIGN = BIT_VALUE (0),
    
    /* Indicate that the boot loader should put information about
       available memory in the Multiboot info structure. */
    MULTIBOOT_GET_MEMORY = BIT_VALUE (1),
    
    /* Indicate that the boot loader should put information about the
       current video mode in the Multiboot info structure. */
    MULTIBOOT_GET_VIDEO_MODE = BIT_VALUE (2),
};

/* Defines. */
#define MULTIBOOT_MAGIC         0x1BADB002
#define MULTIBOOT_FLAGS         (MULTIBOOT_PAGE_ALIGN)

/* More information about the multiboot format can be found in the GNU
   GRUB documentation available on
   http://www.gnu.org/software/grub/. */
/* Type definitions. */
typedef struct
{
    /* The following flags tells if the rest of the fields are
       available. */
    uint32_t has_memory_info           : 1;
    uint32_t has_boot_device_info      : 1;
    uint32_t has_command_line          : 1;
    uint32_t has_module_info           : 1;
    uint32_t has_aout_info             : 1;
    uint32_t has_elf_info              : 1;
    uint32_t has_memory_map            : 1;
    uint32_t has_drives_info           : 1;
    uint32_t has_ROM_config            : 1;
    uint32_t has_boot_loader_name      : 1;
    uint32_t has_APM_info              : 1;
    uint32_t has_video_mode_info       : 1;
    uint32_t reserved                  : 20;

    uint32_t memory_lower;
    uint32_t memory_upper;
    
    uint32_t boot_device;
    
    uint32_t command_line;
    
    uint32_t number_of_modules;
    uint32_t module_base;
    
    /* If has_elf_info is 1 (and it is), those fields are valid. */
    uint32_t section_header_num; /* ? */
    uint32_t section_header_size;
    uint32_t section_header_address;
    uint32_t section_header_string_index;
    
    uint32_t memory_map_length;
    uint32_t memory_map_address;
    
    /* The following are not implemented by GRUB yet.. */
#if FALSE
    uint32_t drives_count;
    uint32_t drives_addr;
    
    uint32_t config_table;
    
    /* Pointer to the boot loader name. */
    
    uint32_t boot_loader_name;
#endif
    
    /* Likewise... */
#if FALSE
    /* Video mode information. */

    uint32_t mode_type;
    uint32_t width;
    uint32_t height;
    uint32_t depth;
    uint32_t frame_buffer_address;
#endif
} __attribute__ ((packed)) multiboot_info_type;

typedef struct
{
    uint32_t start;
    uint32_t end;
    char *name;
    uint32_t reserved;
} __attribute__ ((packed)) multiboot_module_info_type;

typedef struct
{
    uint32_t size;
    uint64_t base_address;
    uint64_t length;
    uint32_t type;
} __attribute__ ((packed)) multiboot_memory_map_type;

/* External variables. */
extern multiboot_info_type multiboot_info;
extern multiboot_module_info_type multiboot_module_info[];
//extern char *memory_map;

/* Function prototypes. */
extern void multiboot_init (void);

#endif /* !__STORM_IA32_MULTIBOOT_H__ */
