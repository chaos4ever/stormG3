/* $chaos: elf.h,v 1.13 2002/10/15 10:04:11 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file        elf.h 
 * @brief       Structures and functions used for decoding ELF images.
 *
 * More information about the ELF format can be found in the ELF
 * specification, as published by the Tool Interface Standards (TIS):
 * http://x86.ddj.com/ftp/manuals/tools/elf.pdf 
 */

#ifndef __STORM_IA32_ELF_H__
#define __STORM_IA32_ELF_H__

#include <storm/types.h>
#include <storm/ia32/bit.h>
#include <storm/ia32/module.h>
#include <storm/ia32/types.h>

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

/* Program types. */
enum
{
    /* A NULL program header means that this segment is unused. */
    ELF_PROGRAM_TYPE_NULL,

    /* A loadable segment. */
    ELF_PROGRAM_TYPE_LOAD,

    /* A segment containing dynamic linking information. */
    ELF_PROGRAM_TYPE_DYNAMIC,

    /* A segment containing a NULL-terminated path to the interpreter
       needed to run this segment. */
    ELF_PROGRAM_TYPE_INTERPRETER,

    /* A segment containig auxiliary information. */
    ELF_PROGRAM_TYPE_NOTE,

    /* A segment with "unspecified semantics". */
    ELF_PROGRAM_TYPE_SHARED_LIBRARY,

    /* A segment containing the program header. */
    ELF_PROGRAM_TYPE_PROGRAM_HEADER,
};

/* Section flags. */
enum
{
    /* This section contains data that should be writable during process
       execution. */
    ELF_SECTION_FLAG_WRITE = BIT_VALUE (0),

    /* This section occupies memory during process execution. */
    ELF_SECTION_FLAG_ALLOCATE = BIT_VALUE (1),

    /* This section contains code that should be executable. */
    ELF_SECTION_FLAG_EXECUTE = BIT_VALUE (2),
};

/* Symbol bindings. */
enum
{
    /* A local symbol. */
    ELF_SYMBOL_BINDING_LOCAL,

    /* A global symbol. */
    ELF_SYMBOL_BINDING_GLOBAL,
    
    /* A "weak" symbol. Similar to a global symbol but with less
       precedence. */
    ELF_SYMBOL__BINDING_WEAK
};

/* Symbol types. */
enum
{
    /* Unspecified symbol type. */
    ELF_SYMBOL_TYPE_NONE,

    /* A data object. (variable, array, etc). */
    ELF_SYMBOL_TYPE_OBJECT,

    /* A function or other executable code. */
    ELF_SYMBOL_FUNC,

    /* A section symbol (used for relocation). */
    ELF_SYMBOL_SECTION,

    /* A file symbol. */
    ELF_SYMBOL_FILE
};

/* Relocation types. */
enum
{
    /* No relocation needs to be performed. */
    ELF_RELOCATION_NONE,

    /* The contents of the relocated place plus the address of the
       symbol. */
    /* ELF_RELOCATION, */ // FIXME: Put a name on this.
    /* The contents of the relocated place plus the address of the
     * symbol, minus the address of the symbol. */
    /* ELF_RELOCATION, */ // FIXME: Put a name on this.
    /* The contents of the relocated place plus the base of the image
       in memory. */
    ELF_RELOCATION_RELATIVE = 8,
    /*    ELF_RELOCATION_ = 32, */
    
};

/**
 * @brief An ELF (Executable and linkable format) header. 
 */
typedef struct 
{
    /**
     * @brief Must be 0x7F, 'E, 'L', 'F' in this order. 
     */
    uint8_t identification[4]; 

    /**
     * @brief The class of this executable. ELF_CLASS_*. 
     */
    uint8_t class;

    /**
     * @brief The endianess of the data in this file. ELF_ENDIAN_* 
     */
    uint8_t endian;

    /**
     * @brief Current version is ELF_VERSION_CURRENT. 
     */
    uint8_t version;

    /**
     * @brief Should be zero.
     *
     * FreeBSD uses those to put 'FreeBSD' in the ELF header. We could
     * do the same...
     */
    uint8_t pad[9];

    /**
     * @brief The type of ELF. ELF_TYPE_*. 
     */
    uint16_t type;   

    /**
     * @brief The machine type this ELF is designed to run
     * on. ELF_MACHINE_WHATEVER. 
     */
    uint16_t machine;

    /**
     * @brief Current version is still ELF_VERSION_CURRENT.
     *
     *(Don't ask me why they put the version ID in two places...) */
    uint32_t version2;

    /**
     * @brief The location of the program entry point. 
     */
    uint32_t entry_point;

    /**
     * @brief Offset of program header table. 
     */
    uint32_t program_header_offset;

    /**
     * @brief Offset of section header table. 
     */
    uint32_t section_header_offset;

    /**
     * @brief FIXME: Document this. 
     */
    uint32_t flags;   

    /**
     * @brief The size of the ELF header. 
     */
    uint16_t elf_header_size;

    /**
     * @brief The size of a program header table entry. 
     */
    uint16_t program_header_entry_size;

    /**
     * @brief The number of program header entries. 
     */
    uint16_t program_header_entries;

    /**
     * @brief The size of a section header table entry. 
     */
    uint16_t section_header_entry_size;

    /**
     * @brief The number of section header entries. 
     */
    uint16_t section_header_entries;

    /**
     * @brief The section header table index of the section name
     * string table. 
     */
    uint16_t section_string_index;
} elf_header_t PACKED;

/**
 * @brief       An ELF section header entry. 
 */
typedef struct
{
    /**
     * @brief The name of the section (index of the string table). 
     */
    uint32_t name;
    uint32_t type;
    uint32_t flags;     

    /**
     * @brief The start of the section in memory. 
     */
    uint32_t address;
  
    /**
     * @brief The start of the section in the file. 
     */
    uint32_t offset;

    /**
     * @brief The size of the section. 
     */
    uint32_t size;
    uint32_t link;     
    uint32_t info;
    uint32_t address_align;

    /**
     * @brief The size of each section entry. 
     */
    uint32_t entry_size;
} elf_section_header_t;

/**
 * @brief       An ELF program header entry. 
 */
typedef struct
{    
    /**
     * @brief The type of this program header, ELF_PROGRAM_TYPE_*. 
     */
    uint32_t type;
    
    /**
     * @brief The offset of this segment, starting from the beginning
     * of the ELF image. 
     */
    uint32_t offset;

    /**
     * @brief The virtual and physical address of this segment in
     * memory.
     */
    uint32_t virtual_address;
    uint32_t physical_address;

    /**
     * @brief Size of this segment in the file. 
     */
    uint32_t file_size;

    /**
     * @brief Size of this segment in memory. 
     */
    uint32_t memory_size;

    /**
     * @brief Flags for this segment, ELF_PROGRAM_FLAG_*. 
     */
    uint32_t flags;

    /** 
     * @brief The number of bytes to which this segment is aligned in
     * memory and in file.
     *
     * Values of 0 and 1 means no specific alignment. 
     */
    uint32_t align;
} elf_program_header_t;

/** 
 * @brief A symbol table entry. 
 */
typedef struct
{
    /**
     * @brief An index into the symbol string table, containing the
     * name of this symbol. 
     */
    uint32_t name;

    /**
     * @brief The value of this symbol. 
     */
    uint32_t value;

    /**
     * @brief The size of this symbol. 0 if no size or size unknown. 
     */
    uint32_t size;

    /**
     * @brief The symbol's type and binding attributes. 
     */
    uint8_t type : 4;
    uint8_t bind : 4;

    /**
     * @brief This field is not used. Only for alignment. 
     */
    uint8_t other;

    /**
     * @brief The index of the section header that this symbol is
     * defined in relation to. 
     */
    uint16_t section_header;
} elf_symbol_t PACKED;

/** 
 * @brief A relocation table entry.
 */
typedef struct
{
    /**
     * @brief The offset in the file that is affected by this
     * relocation. 
     */
    uint32_t offset;

    /**
     * @brief The type of the symbol. 
     */
    uint32_t symbol_type : 8;

    /**
     * @brief The index into the symbol table of this relocation.
     */
    uint32_t symbol_index : 24;
} elf_relocation_t;

/**
 * @brief Our parsed ELF, with some important sections picked out.
 */
typedef struct
{
    /**
     * @brief The ELF header itself. 
     */
    elf_header_t *elf_header;

    /**
     * @brief The section containing strings, used for dynamic linking. 
     */
    elf_section_header_t *string_header;

    /**
     * @brief The section containing the symbol table, used for
     * dynamic linking. 
     */
    elf_section_header_t *symbol_header;

    /**
     * @brief The section containing where in the ELF image the
     * unresolved symbols are so we can resolve them.
     */
    elf_section_header_t *relocation_header;

    /**
     * @brief The image, freshly allocated.
     */
    void *image;
} elf_parsed_t;

/**
 * @brief               Make sure the given ELF is identified properly. 
 * @param elf_header    Pointer to the ELF header.
 */
extern return_t elf_identify (elf_header_t *elf_header);

/**
 * @brief               Parse the given ELF header. 
 * @param elf_header    Pointer to the ELF header. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t elf_parse (elf_header_t *elf_header, elf_parsed_t *elf_parsed);

/**
 * @brief               Resolve unresolved symbols in the given symbol table. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @param function      The list of functions to resolve.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t elf_resolve (elf_parsed_t *elf_parsed, module_function_t *function);

/** 
 * @brief               Relocate relocatable symbols. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @return              STORM_RETURN_SUCCESSFUL if successful.
 */
extern return_t elf_relocate (elf_parsed_t *elf_parsed);

/**
 * @brief               Find the given symbol by index. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @param index         The index of the symbol to find.
 * @param address       Pointer to an address where we store the result.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t elf_symbol_find_by_index (elf_parsed_t *elf_parsed,
                                          unsigned int index, address_t *address);

/** 
 * @brief               Find the given symbol by name. 
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @param name          Pointer to the name of the smbol to find.
 * @param address       Pointer to an address where we store the result.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t elf_symbol_find_by_name (elf_parsed_t *elf_parsed,
                                         const char *name, address_t *address);

/** 
 * @brief Load an ELF.
 * @param elf_parsed    Pointer to the parsed ELF structure.
 * @return              STORM_RETURN_SUCCESS if successful.
 *
 * Allocate memory for it, and copy the data from the different
 * sections there. 
 */
extern return_t elf_load (elf_parsed_t *elf_parsed);

#endif /* !__STORM_IA32_ELF_H__ */
