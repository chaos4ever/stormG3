/* $chaos: return_values.h,v 1.2 2002/07/10 20:02:02 johannes Exp $ */
/* Abstract: Return values for the log library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LOG_RETURN_VALUES_H__
#define __LOG_RETURN_VALUES_H__

enum
{
  /* The function executed successfully. */
  LOG_RETURN_SUCCESS,

  /* One of the arguments to a function was invalid in some way. */
  LOG_RETURN_INVALID_ARGUMENT,

  /* The log service could not be resolved. */
  LOG_RETURN_SERVICE_UNAVAILABLE,
};

#endif /* !__LOG_RETURN_VALUES_H__ */
