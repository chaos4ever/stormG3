/* $chaos: interface.h,v 1.1 2002/10/22 20:59:24 per Exp $ */
/* Abstract: stormG3 kernel interface. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             interface.h
 * @brief            The stormG3 kernel interface.
 *
 * All functions exported to kernel modules and user processes are put
 * into this file.
 */

#ifndef __STORM_INTERFACE_H__
#define __STORM_INTERFACE_H__

/* C99 types. */
#include <stdint.h>

/* Code that should only be accessible from within the kernel and the
   kernel modules. */
#if (defined __STORM_KERNEL_MODULE__) || (defined __STORM_KERNEL__)

/**
 * @brief               Dump the contents of a memory region.
 * @param memory        The address of the memory to dump.
 * @param length        The number of uint32s to dump.
 *
 * The memory is dumped in hexadecimal format.
 */
extern void debug_memory_dump (uint32_t *memory, unsigned int length);

/**
 * @brief               Print a debug message. 
 * @param format_string A printf-compatible format string.
 * @param ...           The data that you want to print.
 */
extern void debug_print (const char *format_string, ...);

/**
 * @brief               Register the given DMA channel. 
 * @param dma_channel   The DMA channel that you want to register.
 * @param dma_buffer    Pointer to the DMA buffer that will be allocated for
 *                      the caller.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t dma_register (unsigned int dma_channel, void **dma_buffer);


/**
 * @brief               Register an IRQ for use by a module. 
 * @param irq_number    The number of the IRQ level to register.
 * @param description   The description of this IRQ handler.
 * @param function      A function pointer to the IRQ handler.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t irq_register (unsigned int irq_number, char *description,
                              irq_handler_t *function);

/**
 * @brief               Allocate global memory. 
 * @param pointer       A double-pointer to the allocated memory.
 * @param size          The size of the memory area to allocate.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t memory_global_allocate (void **pointer, unsigned int size);

/**
 * @brief               Deallocate global memory. 
 * @param pointer       A pointer to the memory that should be deallocated.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t memory_global_deallocate (void *pointer);

/**
 * @brief               Allocate a number of pages. 
 * @param pointer       A double pointer to where the function will put
 *                      a pointer to the allocated memory.
 * @param pages         The number of pages to allocate. (1 is O(1),
 *                      more is much, much slower)
 * @param process_id    The process ID for which to allocate the memory.
 *                      Specify PROCESS_ID_NONE if you do not wish this to
 *                      be stored in the list (it will leak the page if the
 *                      process gets killed in a weird way).
 * @return              STORM_RETURN_SUCCESS if successful.
 */
return_t memory_physical_allocate (void **pointer, unsigned int pages,
                                   process_id_t process_id);


/**
 * @brief               Register a port range. 
 * @param base          The base address of the port range.
 * @param ports         The number of ports to register.
 * @param description   A description of what the ports are used for.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t port_range_register (unsigned int base, size_t ports,
                                     char *description);

/**
 * @brief               Unregister a port range. 
 * @param base          The base address of the port range.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t port_range_unregister (unsigned int base);

/** 
 * @brief               Lookup a service. 
 * @param name          The service name.
 * @param vendor        The vendor of the service provider, i.e. 3Com.
 * @param model         The model of the service provider.
 * @param id            A unique ID for this service provider (to distinguish
 *                      if the vendor and model is the same).
 * @param version       The version of the service.
 * @param services      A pointer to where the number of services found will 
 *                      be put.
 * @param service       An array of services.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t service_lookup (char *name, char *vendor, char *model,
                                char *id, unsigned int version, 
                                size_t *services, service_t **service);

/**
 * @brief               Register a service provider. 
 * @param name          The service name.
 * @param vendor        The vendor of the service provider, i.e. 3Com.
 * @param model         The model of the service provider.
 * @param id            A unique ID for this service provider (to distinguish
 *                      if the vendor and model is the same).
 * @param version       The version of the service.
 * @param service_info  A function pointer to a function that returns
 *                      information about the service.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t service_register (char *name, char *vendor, char *model, 
                                  char *id, unsigned int version,
                                  service_info_t service_info);

/**
 * @brief               Unregister a service provider.
 * @param service       The service name.
 * @param handler       Function pointer to the service handler.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t service_unregister (char *service, function_t handler);

/**
 * @brief               Sleep for the given amount of milliseconds. 
 * @param time          The number of milliseconds to sleep.
 * @return              STORM_RETURN_SUCCESS if successful.
 */
extern return_t timer_sleep_milli (unsigned int time);

#endif /* (defined __STORM_KERNEL_MODULE__) || (defined __STORM_KERNEL__) */

/* Code that's only accessible from within kernel modules. */
#if (defined __STORM_KERNEL_MODULE__)

/** 
 * @brief               The module entry point. 
 */
extern return_t module_start (void);

#endif /* (defined __STORM_KERNEL__MODULE__) */

/* Code that should only be accessible from outside the kernel
   (i.e. system calls). */
#if (! defined __STORM_KERNEL_MODULE__) && (! defined __STORM_KERNEL__)

// system_call (arg1, arg2, arg3, ...)

#endif /* (! defined __STORM_KERNEL_MODULE__) && (! defined __STORM_KERNEL__) */

#endif /* !__STORM_INTERFACE_H__ */
