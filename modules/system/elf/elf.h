/* $chaos: dotfile.emacs,v 1.34 2002/09/30 13:33:00 per Exp $ */
/* Abstract: ELF module header. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/* More information about the ELF format can be found in the ELF
   specification, as published by the Tool Interface Standards (TIS):
   http://x86.ddj.com/ftp/manuals/tools/elf.pdf */

#ifndef __ELF_H__
#define __ELF_H__

#include <storm/storm.h>

/* Enumerations. */
/* File classes. */
enum
{
    /* No class. Bad ELF. */
    ELF_CLASS_NONE,
    
    /* 32-bit ELF. */
    ELF_CLASS_32BIT,

    /* 64-bit ELF. */
    ELF_CLASS_64BIT,
};

/* File types. */
enum
{
    /* No file type. */
    ELF_TYPE_NONE, 
  
    /* Relocatable file (i.e. position independant code, or PIC) */
    ELF_TYPE_RELOCATABLE,
  
    /* Executable file. */
    ELF_TYPE_EXECUTABLE,

    /* Shared object file. */
    ELF_TYPE_DYNAMIC,
  
    /* Core dump. */
    ELF_TYPE_CORE,
};

/* Machine types. */
enum
{
    /* No machne. */
    ELF_MACHINE_NONE,

    /* AT&T WE 32100 */
    ELF_MACHINE_M32,

    /* Sun Sparc. */
    ELF_MACHINE_SPARC,

    /* Intel IA32. */
    ELF_MACHINE_386,

    /* Motorola 68000. */
    ELF_MACHINE_68000,
  
    /* Motorola 88000. */
    ELF_MACHINE_88000,

    /* Intel 80860. */
    ELF_MACHINE_860,

    /* MIPS RS3000. */
    ELF_MACHINE_RS3000,
};

/* ELF versions. */
enum
{
    /* Invalid version. */
    ELF_VERSION_NONE,

    /* Current version. */
    ELF_VERSION_CURRENT,
};

/* Endianess. */
enum
{
    /* No endian (invalid). */
    ELF_ENDIAN_NONE,

    /* Little endian (LSB). */
    ELF_ENDIAN_LITTLE,

    /* Big endian (MSB). */
    ELF_ENDIAN_BIG,
};

/* Section types. */
enum
{
    /* This section is inactive. */
    ELF_SECTION_TYPE_NULL,

    /* This section is used for something defined by the program
       itself. */
    ELF_SECTION_TYPE_UNDEFINED,

    /* This section holds the symbol table. May only exist once in the
       file. */
    ELF_SECTION_TYPE_SYMBOL_TABLE,

    /* This section holds the string table. May only exist once in the
       file. */
    ELF_SECTION_TYPE_STRING_TABLE,

    /* This section holds relocation entries with explicit addends
       (?). */
    ELF_SECTION_TYPE_RELOCATION_ADDENDS,

    /* This section holds a symbol hash table. */
    ELF_SECTION_TYPE_SYMBOL_HASH_TABLE,
  
    /* This section holds information for dynamic linking. */
    ELF_SECTION_TYPE_DYNAMIC,

    /* This section holds information that marks the file in some
       way. */
    ELF_SECTION_TYPE_NOTE,

    /* This section does not take up any space in the ELF file. Most
       often used for BSS sections. */
    ELF_SECTION_TYPE_NO_SPACE,

    /* This section holds relocation entries without explicit
       addends. */
    ELF_SECTION_TYPE_RELOCATION,
  
    /* This section type is reserved by has unspecified
       semantics. Programs that contain a section of this type does not
       conform to the ABI. */
    ELF_SECTION_TYPE_SHARED_LIBRARY,
    
    /* This section holds a symbol table used for dynamic linking. */
    ELF_SECTION_TYPE_DYNAMIC_SYMBOL_TABLE,
};

/* Type definitions. */
/* An ELF (Executable and linkable format) header. */
typedef struct 
{
    /* Must be 0x7F, 'E, 'L', 'F' in this order. */
    uint8_t identification[4]; 

    /* The class of this executable. ELF_CLASS_*. */
    uint8_t class;

    /* The endianess of the data in this file. ELF_ENDIAN_* */
    uint8_t endian;

    /* Current version is ELF_VERSION_CURRENT. */
    uint8_t version;

    /* Should be zero. FreeBSD uses those to put 'FreeBSD' in the ELF
       header. We could do the same... */
    uint8_t pad[9];

    /* The type of ELF. ELF_TYPE_*. */
    uint16_t type;   

    /* The machine type this ELF is designed to run
       on. ELF_MACHINE_WHATEVER. */
    uint16_t machine;

    /* Current version is still ELF_VERSION_CURRENT. (Don't ask me why
       they put the version ID in two places...) */
    uint32_t version2;

    /* The location of the program entry point. */
    uint32_t entry_point;

    /* Offset of program header table. */
    uint32_t program_header_offset;

    /* Offset of section header table. */
    uint32_t section_header_offset;
    uint32_t flags;   

    /* The size of the ELF header. */
    uint16_t elf_header_size;

    /* The size of a program header table entry. */
    uint16_t program_header_entry_size;

    /* The number of program header entries. */
    uint16_t program_header_entries;

    /* The size of a section header table entry. */
    uint16_t section_header_entry_size;

    /* The number of section header entries. */
    uint16_t section_header_entries;

    /* The section header table index of the section name string
       table. */
    uint16_t section_string_index;
} __attribute__ ((packed)) elf_header_t;

#endif /* !__ELF_H__ */
