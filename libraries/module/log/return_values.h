/* $chaos: return_values.h,v 1.1 2002/12/12 21:59:41 per Exp $ */
/* Abstract: Return values for the log library. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __LOG_RETURN_VALUES_H__
#define __LOG_RETURN_VALUES_H__

enum log_return_t
{
  /* The function executed successfully. */
  LOG_RETURN_SUCCESS,

  /* One of the arguments to a function was invalid in some way. */
  LOG_RETURN_INVALID_ARGUMENT,

  /* The log service could not be resolved. */
  LOG_RETURN_SERVICE_UNAVAILABLE,
};

#endif /* !__LOG_RETURN_VALUES_H__ */
