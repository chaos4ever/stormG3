/* $chaos: types.h,v 1.4 2002/07/12 09:46:23 johannes Exp $ */
/* Abstract: Ethernet library types. */
/* Author: Johannes Lundberg <jojo@chaosdev.org>
           Håkan Larsson     <trc@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __ETHERNET_TYPES_H__
#define __ETHERNET_TYPES_H__

typedef char ethernet_address_t;

typedef struct
{
  ethernet_address_t destination;
  ethernet_address_t source;
  uint16_t protocol; // FIXME
  char data[0];
} ethernet_packet_t;

typedef return_t (*ethernet_receiver_t)(ethernet_packet_t, int);

typedef struct
{
  ethernet_address_t mac_address;
  void *ull;
  /* FIXME: Finish this. */
} ethernet_info_t;

/* Functions provided by ethernet modules. */
typedef return_t (*ethernet_send_t)(ethernet_packet_t *, int);
typedef return_t (*ethernet_send_raw_t)(ethernet_packet_t *, int);
typedef return_t (*ethernet_protocol_register_t)(int, ethernet_receiver_t);
typedef return_t (*ethernet_protocol_unregister_t)(int, ethernet_receiver_t);
typedef return_t (*ethernet_info_get_t)(ethernet_info_t);
typedef return_t (*ethernet_info_set_t)(ethernet_info_t);

/* An ethernet service. */
typedef struct
{
  /* The magic cookie (Den magiska kakan). */
  unsigned int magic_cookie;
  
  ethernet_send_t send;
  ethernet_send_raw_t send_raw;
  ethernet_protocol_register_t protocol_register;
  ethernet_protocol_unregister_t protocol_unregister;
  ethernet_info_get_t info_get;
  ethernet_info_set_t info_set;
} ethernet_service_t;

/* Initialization function. */
typedef return_t (*ethernet_init_t)(ethernet_service_t *);

#endif /* !__ETHERNET_TYPES_H__ */
