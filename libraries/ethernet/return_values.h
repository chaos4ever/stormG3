/* $chaos: return_values.h,v 1.2 2002/07/11 21:29:25 per Exp $ */
/* Abstract: Return values for the ethernet library. */
/* Author: Johannes Lundberg <jojo@chaosdev.org> 
           Håkan Larsson     <trc@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __ETHERNET_RETURN_VALUES_H__
#define __ETHERNET_RETURN_VALUES_H__

enum
{
  /* The function executed successfully. */
  ETHERNET_RETURN_SUCCESS,

  /* Bad protocol specified to protocol_register or protocol_unregister. */
  ETHERNET_RETURN_BAD_PROTOCOL,

  /* Bad function pointer */
  ETHERNET_RETURN_BAD_FUNCTION_POINTER,

  /* Operation not supported by the module. */
  ETHERNET_RETURN_OPERATION_NOT_SUPPORTED,

  /* FIXME: Add more later. */
};

#endif /* !__ETHERNET_RETURN_VALUES_H__ */
