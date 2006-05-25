/* $chaos: soundblaster.c,v 1.3 2002/12/03 21:54:43 per Exp $ */
/* Abstract: Sound Blaster server */

/* Authors: Per Lundberg <per@chaosdev.org> 
   Erik Moren <nemo@chaosdev.org> */

/* Copyright 1999-2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/* Most of the information in this server is based on information
   found in sblaster.doc, which can be found in the same directory as
   this source code. */

#include <storm/storm.h>
#include <log/log.h>
#include <sound/sound.h>

#include "soundblaster.h"

/* The log service provider that we are using. */
log_service_t log;

/* The default base port of the sound card. Can be overridden by a
   command parameter to the server (well, in the future...) */
uint8_t *dma_buffer;
double_buffer_t double_buffer[2];
unsigned int current_buffer = 0;

/* Change these to fit your needs. */
uint16_t base_port = 0x220;
unsigned int irq = 5;
unsigned int dma_channel = 1;

/* Version of the card. Valid versions are (from SBLASTER.DOC):

SoundBlaster 1.0           1.??  (1.05???)
SoundBlaster 1.5           1.??  (1.05???)
SoundBlaster 2.0           2.xx  (2.01)
SoundBlaster Pro           3.00  (???)
SoundBlaster Pro 2         3.01+ (3.01, 3.02)
SoundBlaster 16            4.0x  (4.04, 4.05)
SoundBlaster 16 SCSI-2     4.11  (4.11)
SoundBlaster AWE32         4.12+ (4.12) */
uint8_t major_version, minor_version;

/* FIXME: They should not be global variables, perhaps not even
   separate ones. */
soundblaster_device_t soundblaster_device;
soundblaster_event_t soundblaster_event;

static void dsp_write (uint8_t data)
{
    while ((port_uint8_in (DSP_DATA_WRITE) & 0x80) != 0);
    port_uint8_out (DSP_DATA_WRITE, (data));
}

static uint8_t dsp_read (void)
{
    while ((port_uint8_in (DSP_DATA_AVAILABLE) & 0x80) == 0);
    return port_uint8_in (DSP_DATA_READ);
}

#if FALSE
static uint8_t dsp_mixer_read (uint8_t which_register)
{
    port_uint8_out (DSP_MIXER_REGISTER, which_register);
    return port_uint8_in (DSP_MIXER_DATA);
}
#endif

static void dsp_mixer_write (uint8_t which_register, uint8_t data)
{
    port_uint8_out (DSP_MIXER_REGISTER, which_register);
    port_uint8_out (DSP_MIXER_DATA, data);
}

/* Detect if there is some kind of sound blaster card in this
   machine. */
static bool detect_sb (void)
{
    /* Register the I/O ports so that we can probe for the card. */
    if (port_range_register (base_port, 16, "Sound Blaster"))
    {
        log.print (LOG_URGENCY_EMERGENCY, "Failed to register ports.\n");
        return FALSE;
    }

    /* Reset the DSP. */
    port_uint8_out (DSP_RESET, 0x01);
    timer_sleep_milli (4);
    port_uint8_out (DSP_RESET, 0x00);
  
    /* FIXME: Should only wait for a maximum of 100 us. */
    while ((port_uint8_in (DSP_DATA_AVAILABLE) & (1 << 7)) == 0);

    /* Check if the DSP was reset successfully. */
    if (port_uint8_in (DSP_DATA_READ) == 0xAA)
    {
        /* Let's check which kind of SB this is. */
        dsp_write (DSP_VERSION);
        major_version = dsp_read ();
        minor_version = dsp_read ();
    
        return TRUE;
    }
    else
    {
        port_range_unregister (base_port);
        return FALSE;
    }
}

/* Get information about the soundblaster service. */
static return_t soundblaster_info (void *info UNUSED)
{
    return STORM_RETURN_NOT_IMPLEMENTED;
}

/* Main function. */
return_t module_start (void)
{
    if (log_lookup (&log) != LOG_RETURN_SUCCESS)
    {
        return -1;
    }

    /* Check for the presence of a Sound Blaster compatible card. */
    if (!detect_sb ())
    {
        log.print (LOG_URGENCY_EMERGENCY,
                   "No Sound Blaster compatible card detected.");
        return -1;
    }
    else
    {
        switch (major_version)
        {
            case 1:
            {
                log.print (LOG_URGENCY_INFORMATIVE,
                           "Sound Blaster 1.0/1.5 detected.");
                break;
            }
            case 2:
            {
                log.print (LOG_URGENCY_INFORMATIVE,
                           "Sound Blaster 2.0 detected.");
                break;
            }
            case 3:
            {
                log.print (LOG_URGENCY_INFORMATIVE,
                           "Sound Blaster Pro detected.");
                break;
            }
            case 4:
            {
                switch (minor_version)
                {
                    case 1 ... 11:
                    case 13:
                    {
                        log.print (LOG_URGENCY_INFORMATIVE,
                                   "Sound Blaster 16 detected.");

                        /* Set IRQ 5 and DMA 1. FIXME: Do this in a
                           cleaner way. */
                        dsp_mixer_write (0x80, 2);
                        dsp_mixer_write (0x81, 2);
              
                        /* Set the volume. */
                        dsp_mixer_write (0x22, 0xFF);
                        break;
                    }
                    case 12:
                    {
                        log.print (LOG_URGENCY_INFORMATIVE,
                                   "Sound Blaster AWE32 detected.");
                        break;
                    }
                    default:
                    {
                        log.print (LOG_URGENCY_INFORMATIVE,
                                   "Some kind of 16-bit Sound Blaster (compatible) detected.");
                        break;
                    }
                }
            }
        }
    }

    /* Because we only support soundblaster 2.0-functionality, treat
       every card as a sb2.0 whatever card is installed */
    soundblaster_device.irq = irq;
    soundblaster_device.base_port = base_port;
    soundblaster_device.dma_channel = dma_channel;
    soundblaster_device.max_frequency_output = 22050;
    soundblaster_device.supports_8bit_output = TRUE;
    soundblaster_device.supports_16bit_output = FALSE;
    soundblaster_device.supports_autoinit_dma = TRUE;
    soundblaster_device.device_name = "Sound Blaster 2.0";

    void *p;

    /* Register the DMA channel. */
    if (dma_register (soundblaster_device.dma_channel,
                      (void **) &p) != STORM_RETURN_SUCCESS)
    {
        log.print_formatted (LOG_URGENCY_INFORMATIVE,
                             "Failed to register DMA channel %u.",
                             soundblaster_device.dma_channel);
        return -1;
    }

    dma_buffer = p;

    dsp_write (DSP_SPEAKER_ON);
  
    if (irq_register (soundblaster_device.irq, "Soundblaster",
                      (irq_handler_t *) &irq_handler) != STORM_RETURN_SUCCESS)
    {
        log.print_formatted (LOG_URGENCY_EMERGENCY,
                             "Could not allocate IRQ %u.", 
                             soundblaster_device.irq);
        return -1;
    }

    /* Okay, all set. Now, go ahead and register the sound service. */
    service_register_t service_register_info;
    service_register_info.service_vendor = "chaos development";
    service_register_info.device_vendor = "Creative";
    // FIXME: Change this to the actual model. 
    service_register_info.model = "Sound Blaster";
    service_register_info.device_id = "1";
    service_register_info.info_handler = &soundblaster_info;

    // FIXME: Add our methods here.
    service_method_t service_method[] UNUSED = 
        {
            { -1, NULL }
        };

    return sound_register (&service_register_info, service_method);
}
 
/* Handle interrupts. */
void irq_handler (unsigned int irq_number UNUSED)
{
    /* Clear the SB interrupt. */
    port_uint8_in (DSP_DATA_AVAILABLE);
        
    /* If only a single sample was being played, do some stuff. */
    if (!soundblaster_event.streaming)
    {
        soundblaster_event.is_playing = FALSE;
        dsp_write (DSP_SPEAKER_OFF);
    }
}
