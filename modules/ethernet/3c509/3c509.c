/* $chaos$ */
/* Abstract: 3Com Etherlink III module (3c509) */
/* Author: Johannes Lundberg <jojo@chaosdev.org>
           Håkan Larsson     <trc@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */
=======

#include <storm/storm.h>

#include <log/log.h>
#include <ethernet/ethernet.h>

#include <3c509.h>

#define ETHERNET_MODULE_VERSION 1
#define unused __attribute__ ((unused))

log_service_t log;

static return_t ethernet_send (ethernet_packet_t *packet unused, int length unused)
{
  return ETHERNET_RETURN_OPERATION_NOT_SUPPORTED;
}

static return_t ethernet_send_raw (ethernet_packet_t *packet unused, int length unused)
{
  return ETHERNET_RETURN_OPERATION_NOT_SUPPORTED;
}

static return_t ethernet_protocol_register
                  (int protocol unused, ethernet_receiver_t ethernet_receiver unused)
{
  return ETHERNET_RETURN_OPERATION_NOT_SUPPORTED;
}

static return_t ethernet_protocol_unregister
                  (int protocol unused, ethernet_receiver_t ethernet_receiver unused)
{
  return ETHERNET_RETURN_OPERATION_NOT_SUPPORTED;
}

static return_t ethernet_info_get (ethernet_info_t ethernet_info unused)
{
  return ETHERNET_RETURN_OPERATION_NOT_SUPPORTED;
}

static return_t ethernet_info_set (ethernet_info_t ethernet_info unused)
{
  return ETHERNET_RETURN_OPERATION_NOT_SUPPORTED;
}

static return_t service_info (void *ethernet_void)
{
  ethernet_service_t *ethernet_service = (ethernet_service_t *) ethernet_void;

  ethernet_service->magic_cookie        = ETHERNET_COOKIE;
  ethernet_service->send                = &ethernet_send;
  ethernet_service->send_raw            = &ethernet_send_raw;
  ethernet_service->protocol_register   = &ethernet_protocol_register;
  ethernet_service->protocol_unregister = &ethernet_protocol_unregister;

  return STORM_RETURN_SUCCESS;
}

return_t probe (void)
{
  int id_port = 0x110;

  /* Select an open I/O location at 0x1*0, and probe for the 3c509 card. */

  for ( ; id_port < 0x200; id_port += 0x10)
  {
    if (port_range_register (id_port, 1 , "3Com Etherlink III ID port") !=
        STORM_RETURN_SUCCES)
    {
      continue;
    }
    port_out (id_port, 0x00);
    port_out (id_port, 0xFF);
    if (port_in_u8 (id_port) & 0x01)
    {
      break;
    }
  } 

  if (id_port >= 0x200)
  {
    
  }
} 

return_t module_start (void)
{
  log_init (&log);
  if (probe ())
  {
    
  }

  log.print (LOG_URGENCY_DEBUG, "3c509 module initializing.");

  return service_register ("ethernet", "chaos development", "3c509",
                           "0", ETHERNET_MODULE_VERSION, &service_info);
}
