/* $chaos: memory_virtual.h,v 1.1 2002/06/09 15:04:52 per Exp $ */
/* Abstract: Virtual memory prototypes and data structures. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __STORM_IA32_MEMORY_VIRTUAL_H__
#define __STORM_IA32_MEMORY_VIRTUAL_H__

/* Defines. */
/* Supervisor-only, read-only (since we don't set WP bit, it isn't
   really read-only for the kernel..), and global. */
#define PAGE_KERNEL             PAGE_GLOBAL

/* Standard flags. */
#define PAGE_WRITABLE           BIT_VALUE (0)
#define PAGE_NON_PRIVILEGED     BIT_VALUE (1)
#define PAGE_WRITE_THROUGH      BIT_VALUE (2)
#define PAGE_CACHE_DISABLE      BIT_VALUE (3)
#define PAGE_GLOBAL             BIT_VALUE (4)

/* The following flags are used when creating new entries in the page
   directory. We let the page table set everything, so we need to have
   this all-privileged. */
#define PAGE_DIRECTORY_FLAGS     (PAGE_WRITABLE | PAGE_NON_PRIVILEGED)

/* Structures. */
typedef struct
{
  uint32_t present              : 1;
  uint32_t flags                : 4;
  uint32_t accessed             : 1;
  uint32_t dirty                : 1;

  /* Should always be one. */
  uint32_t page_size            : 1;
  uint32_t global               : 1;
  uint32_t available            : 3;

  /* Obvious? */
  uint32_t zero                 : 10;
  uint32_t page_base            : 10;
} page_directory_4mb_t;

typedef struct
{
  uint32_t present              : 1;
  uint32_t flags                : 4;
  uint32_t accessed             : 1;
  uint32_t zero                 : 1;

  /* Should always be zero. */
  uint32_t page_size            : 1;
  uint32_t global               : 1;
  uint32_t available            : 3;
  uint32_t page_table_base      : 20;
} page_directory_t;

typedef struct
{
  uint32_t present              : 1;
  uint32_t flags                : 4;
  uint32_t accessed             : 1;
  uint32_t dirty                : 1;
  uint32_t zero                 : 1;
  uint32_t global               : 1;
  uint32_t available            : 3;
  uint32_t page_base            : 20;
} page_table_t;

/* Prototypes. */
/* Initialize the virtual memory system. */
extern void memory_virtual_init (void);

/* Map memory. */
extern void memory_virtual_map (page_directory_t *page_directory,
                                uint32_t virtual_page, 
                                uint32_t physical_page, unsigned int pages,
                                uint32_t flags);

#endif /* !__STORM_IA32_MEMORY_VIRTUAL_H__ */
