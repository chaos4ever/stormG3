/* $chaos: magic_cookies.h,v 1.2 2002/10/04 19:01:19 per Exp $ */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/** 
 * @file magic_cookies.h
 * @brief Magic cookies. 
 */

#ifndef __STORM_MAGIC_COOKIES_H__
#define __STORM_MAGIC_COOKIES_H__

/* The magic cookie base. */
#define MAGIC_COOKIE_BASE               0xC0CAC01A

/* Magic cookie for global memory slabs. */
#define GLOBAL_SLAB_COOKIE              (MAGIC_COOKIE_BASE + 0x10)

/* Magic cookie for global memory pages. */
#define GLOBAL_PAGE_COOKIE              (MAGIC_COOKIE_BASE + 0x20)

#endif /* !__STORM_MAGIC_COOKIES_H__ */
