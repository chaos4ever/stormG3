/* $chaos$ */
/* Abstract: <some NIC-controller> ethernet module. */
/* Author: Your Name <your@email> */
           
/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#include <storm/storm.h>

#include <ethernet/ethernet.h>

#define unused __attribute__ ((unused))

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

return_t module_start (void)
{
  return service_register ("ethernet", "chaos development", "some-nic",
                           "0", ETHERNET_SERVICE_VERSION, &service_info);
}
