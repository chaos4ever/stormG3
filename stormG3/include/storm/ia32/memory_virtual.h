/* $chaos: memory_virtual.h,v 1.6 2002/10/11 07:44:04 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file                        memory_virtual.h
 * @brief                       Virtual memory prototypes and data structures. 
 */

#ifndef __STORM_IA32_MEMORY_VIRTUAL_H__
#define __STORM_IA32_MEMORY_VIRTUAL_H__

/**
 * @brief               Pages owned by the kernel.
 *
 * Supervisor-only, read-only (since we don't set WP bit, it isn't
 * really read-only for the kernel..), and global. 
 */
#define PAGE_KERNEL     PAGE_GLOBAL

/**
 * @brief               Pages owned by user processes.
 */
#define PAGE_USER       (PAGE_NON_PRIVILEGED | PAGE_WRITABLE | \
                         PAGE_WRITE_THROUGH)

/**
 * @brief               Is the page writable?
 */
#define PAGE_WRITABLE   BIT_VALUE (0)

/**
 * @brief               Can the page be accessed from nonprivileged (ring 3)
 *                      code?
 */
#define PAGE_NON_PRIVILEGED \
                        BIT_VALUE (1)

/**
 * @brief               Is write-through cache enabled for the page?
 */
#define PAGE_WRITE_THROUGH \
                        BIT_VALUE (2)

/**
 * @brief               Is caching completely disabled for this page?
 *
 * This flag is neccessary to use when mapping I/O devices.
 */
#define PAGE_CACHE_DISABLE \
                        BIT_VALUE (3)

/**
 * @brief               Is this a global page, shared between all page
 *                      directories?
 */
#define PAGE_GLOBAL     BIT_VALUE (4)

/**
 * @brief               Flags used when creating new entries in the page
 *                      directory.
 *
 * We let the page table set everything, so we need to have this
 * all-privileged. 
 */
#define PAGE_DIRECTORY_FLAGS \
                        (PAGE_WRITABLE | PAGE_NON_PRIVILEGED)

/**
 * @brief               A page number. 
 */
typedef                 uint32_t page_number_t;

/**
 * @brief               A page directory entry (PDE) when using 4MiB pages. 
 */
typedef struct
{
    uint32_t            present              : 1;
    uint32_t            flags                : 4;
    uint32_t            accessed             : 1;
    uint32_t            dirty                : 1;
    
    /**
     * @brief           Should always be one (4 MiB pages, no page 
     *                  tables). 
     */
    uint32_t            page_size            : 1;
    uint32_t            global               : 1;
    uint32_t            available            : 3;
    
    /**
     * @brief           Should always be zero.
     */
    uint32_t            zero                 : 10;

    /**
     * @brief           The physical base of this page, shifted 20 steps 
     *                  to the right.
     */
    uint32_t            page_base            : 10;
} page_directory_4mb_t;

/**
 * @brief               A page directory entry (PDE).
 */
typedef struct
{
    uint32_t            present              : 1;
    uint32_t            flags                : 4;
    uint32_t            accessed             : 1;
    uint32_t            zero                 : 1;
    
    /**
     * @brief           Should always be zero (4 KiB pages).
     */
    uint32_t            page_size            : 1;
    uint32_t            global               : 1;
    uint32_t            available            : 3;
    uint32_t            page_table_base      : 20;
} page_directory_t;

/**
 * @brief A page table entry (PTE). 
 */
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

/** 
 * @brief Initialize the virtual memory system. 
 */
extern void memory_virtual_init (void);

/**
 * @brief               Map memory into the given page directory. 
 * @param page_directory
 *                      The page directory in which to map.
 * @param virtual_page  The virtual page base.
 * @param physical_page The physical page base.
 * @param pages         The number of pages to map.
 * @param flags         The page flags to use.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
return_t memory_virtual_map (page_directory_t *page_directory,
                             page_number_t virtual_page, 
                             page_number_t physical_page,
                             unsigned int pages,
                             uint32_t flags);

#endif /* !__STORM_IA32_MEMORY_VIRTUAL_H__ */
