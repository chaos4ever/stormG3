/* $chaos */

#include <storm/storm.h>

#include <ethernet/ethernet.h>

#define ETHERNET_MODULE_VERSION 1
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
  debug_print ("Tjolahopp\n");
  return service_register ("3c509", "chaos development", "3c509",
                           "0", ETHERNET_MODULE_VERSION, &service_info);
}
