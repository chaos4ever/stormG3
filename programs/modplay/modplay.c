/* $chaos: modplay.c,v 1.4 2002/12/17 22:05:20 per Exp $ */
/* Abstract: Module player. */
/* Author: Erik Moren <nemo@chaosdev.org> */

/* Copyright 1999-2000, 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#include <storm/storm.h>
#include <console/console.h>
#include <kernel/kernel.h>
#include <log/log.h>
#include <memory/memory.h>
#include <sound/sound.h>

#include "modfile.h"
#include "modplay.h"

channel_type channel[CHANNELS];

sample_type sample[31];
uint8_t *pattern_data;
uint8_t *pattern[256];

unsigned int bpm;
unsigned int speed;
unsigned int mix_length;
unsigned int pattern_ticks;
unsigned int current_pattern;
unsigned int tick_length;
int current_row;

/* Services. */
log_service_t log;
kernel_service_t kernel;
console_service_t console;
sound_service_t sound;

int main (void)
{
    /*
     * Get a connection with the log service.
     */
    if (log_init (&log) != LOG_RETURN_SUCCESS)
    {
        return -1;
    }

    /*
     * Get a connection with the kernel service.
     */
    if (kernel_init (&kernel) != KERNEL_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY,
                    "Failed connecting to kernel service");
        return -1;
    }

    /*
     * Set the process and thread name.
     */
    kernel.set_process_name (PROGRAM_NAME);
    kernel.set_thread_name ("Playing module...");

    /*
     * Get a connection with the console service.
     */
    if (console_init (&console) != CONSOLE_RETURN_SUCCESS)
    {
        return -1;
    }

    /*
     * Open a virtual console.
     */
    console.open (80, 50, 4, VIDEO_MODE_TYPE_TEXT);
    console.use_keyboard (TRUE, CONSOLE_KEYBOARD_NORMAL);
    console.clear ();
    console.print ("Module player\n");

    if (sound_init (&sound) != SOUND_RETURN_SUCCESS)
    {
        log.print (LOG_URGENCY_EMERGENCY,
                    "Could not establish connection to a sound service.");
        return -1;
    }

    log.print (LOG_URGENCY_EMERGENCY,
                "Found sound service and established connection.");

    load_module ();
    memory_allocate ((void **) &sound_message,
                     sizeof (sound_message_type) + BUFFER_SIZE);
    sound_message->length = BUFFER_SIZE;
    sound_message->frequency = FREQUENCY;
    sound_message->bits = 8;

    /* Just some init data to get things going. */

    current_pattern = 0;
    current_row = 0;
    bpm = 125;
    speed = 6;
    tick_length = speed * ((FREQUENCY * 5) / bpm) >> 1;
    pattern_ticks = tick_length + 1;

    channel[0].volume = 63;
    channel[1].volume = 63;
    channel[2].volume = 63;
    channel[3].volume = 63;

#if FALSE
    note = (note_type *) pattern_data;
    for (i = 0; i < 10; i++)
    {
        console_print_formatted (&console_structure, "\n%x  %x",
                                 note->sample_number, note->period_frequency);
        note++;
        console_print_formatted (&console_structure, " | %x  %x",
                                 note->sample_number, note->period_frequency);
        note++;
        console_print_formatted (&console_structure, " | %x  %x",
                                 note->sample_number, note->period_frequency);
        note++;
        console_print_formatted (&console_structure, " | %x  %x",
                                 note->sample_number, note->period_frequency);
        note++;
    }
#endif

    while (TRUE)
    {
        fill_buffer (sound_message->data);

        if (sound.play_stream (sound_message) != SOUND_RETURN_SUCCESS)
        {
            log.print (LOG_URGENCY_EMERGENCY,
                       "Could not play the sample as wanted.");
            return -1;
        }
        
        console.cursor_move (0, 5);
        console.print_formatted ("Current Pattern: %x  "
                                 "\nCurrent Row: %x  ",
                                 current_pattern, current_row);
        console.print_formatted ("Speed: %x  "
                                 "\nBPM: %x  ",
                                 speed, bpm);
        
        /*    console_print_formatted (&console_structure, "\n%x %x %x   %x",
              current_row, channel[0].sample_number,
              channel[0].period_frequency,
              channel[0].scaling_factor); */
    }
    
    return 0;
}

void load_module (void)
{
    unsigned int i, j;
    unsigned int current_position;
    uint8_t temp_char1;
    uint8_t temp_char2;
    note_type *note;
    uint8_t temp_note[4];
    uint8_t *modfile_ptr;

#if FALSE
    /* Check to see if the module is of type "M.K." -> 31 channels. */
    if (string_compare_max("M.K.", &modfile[1080], 4) == 0)
    {
        //console_print(&console_structure, "\nModfile is of type M.K.");
    }
#endif

    /* Fetch module name. */

    memory_copy (module.name, &modfile[0], 20);
    module.name[19] = '\0';

    /* Fetch the sample data. */

    for (i = 0; i < 31; i++)
    {
        memory_copy (sample[i].name, &modfile[20 + i * 30], 22);
        sample[i].name[21] = '\0';
        temp_char1 = modfile[20 + i * 30 + 22];
        temp_char2 = modfile[20 + i * 30 + 23];
        sample[i].length = ((uint16_t) temp_char1 * 256 + temp_char2) * 2;
        sample[i].finetune = modfile[20 + i * 30 + 24];
        sample[i].volume = modfile[20 + i * 30 + 25];
        temp_char1 = modfile[20 + i * 30 + 26];
        temp_char2 = modfile[20 + i * 30 + 27];
        sample[i].repeat_point = ((uint16_t) temp_char1 * 256 + temp_char2) * 2;
        temp_char1 = modfile[20 + i * 30 + 28];
        temp_char2 = modfile[20 + i * 30 + 29];
        sample[i].repeat_length = ((uint16_t) temp_char1 * 256 + temp_char2) * 2;
    }

    /* Load the song length (number of patterns to play), pattern
       sequence and the 4 id bytes (eg. 'M.K.'). */

    module.song_length = modfile[950];
    memory_copy (module.play_sequence, &modfile[952], 128);
    memory_copy (module.id, &modfile[1080], 4);

    /*
      console_print(&console_structure,"\nplay_sequence: ");
      for (i = 0; i < 128; i++)
      {
      console_print_formatted(&console_structure,"%x: %x | ",
      i, module.play_sequence[i]);
      }
    */

    /* Check to see how many different patterns we got. */

    module.physical_patterns = 0;

    for (i = 0; i < 128; i++)
    {
        if (module.play_sequence[i] > module.physical_patterns)
        {
            module.physical_patterns = module.play_sequence[i];
        }
    }
    module.physical_patterns++;
    console.print_formatted ("\nPhysical patterns: %x",
                              module.physical_patterns);

    /* Allocate memory for the pattern data and fill it. */

    memory_allocate ((void **) &pattern_data,
                     module.physical_patterns * BYTES_PER_PATTERN);

    /* We have to rearrange the order of the notedata because it is
       originally arranged in a really weird way. */

    note = (note_type *) pattern_data;
    modfile_ptr = (uint8_t *) &modfile[1084];

    for (i = 0; i < module.physical_patterns; i++)
    {
        for (j = 0; j < ROWS * CHANNELS; j++)
        {
            memory_copy (temp_note, modfile_ptr, 4);
            note->sample_number = (temp_note[0] & 0xF0) | ((temp_note[2] & 0xF0) >> 4);
            note->period_frequency = (uint16_t) ((temp_note[0] & 0x0F) << 8) | temp_note[1];
            note->effect_number = temp_note[2] & 0x0F;
            note->effect_parameter = temp_note[3];

            modfile_ptr += 4;
            note++;
        }

        pattern[i] = &pattern_data[i * BYTES_PER_PATTERN];
    }

    /* Allocate memory for the samples and fill them. */

    current_position = 1084 + module.physical_patterns * BYTES_PER_PATTERN;

    for (i = 0; i < 31; i++)
    {
        /* If sample length is 0, then it's no idea to allocate and store it. */

        if (sample[i].length != 0)
        {
            memory_allocate ((void **) &sample[i].data, sample[i].length);
            for (j = 0; j < sample[i].length; j++)
            {
                sample[i].data[j] = modfile[current_position + j] ^ 0x80; /* XOR 80h */
            }
        }
        current_position += sample[i].length;
    }
}

void fill_buffer (uint8_t *buffer)
{
    unsigned int i, j;
    uint32_t k;
    note_type *note;
    uint16_t data;
    
    for (i = 0; i < BUFFER_SIZE; i++)
    {
        if (pattern_ticks++ > tick_length)
        {
            note = (note_type *) pattern[module.play_sequence[current_pattern]];
            note += (current_row * CHANNELS);
            
            current_row++;
            
            do_note (note + 0, channel + 0);
            do_note (note + 1, channel + 1);
            do_note (note + 2, channel + 2);
            do_note (note + 3, channel + 3);

            if (current_row == ROWS)
            {
                current_row = 0;
                current_pattern++;

                if (current_pattern == module.song_length)
                {
                    current_pattern = 0;
                }
            }

            pattern_ticks = 0;
        }

        data = 0;

        for (j = 0; j < CHANNELS; j++)
        {
            channel[j].ticks += channel[j].scaling_factor;
            k = (channel[j].ticks >> 16);

            if (k >= channel[j].length)
            {
                channel[j].sample_data += channel[j].repeat_point;
                channel[j].length = channel[j].repeat_length;
                channel[j].repeat_point = 0;
                channel[j].ticks = 0;
                data += sample[channel[j].sample_number].data[0] * channel[j].volume;
            }
            else
            {
                data += sample[channel[j].sample_number].data[k] * channel[j].volume;
            }
        }

        buffer[i] = data >> 8;
    }
}

void do_note (note_type *work_note, channel_type *work_channel)
{
    if (work_note->period_frequency != 0)
    {
        if (work_note->sample_number != 0)
        {
            work_channel->sample_number = work_note->sample_number - 1;
        }

        work_channel->sample_data = sample[work_channel->sample_number].data;
        work_channel->length = sample[work_channel->sample_number].length;
        work_channel->repeat_point =
            sample[work_channel->sample_number].repeat_point;
        work_channel->repeat_length =
            sample[work_channel->sample_number].repeat_length;
        work_channel->period_frequency =
            work_note->period_frequency;
        work_channel->ticks = 0;

        work_channel->scaling_factor =
            (PAL / (uint32_t) (work_channel->period_frequency)) << 8;
        work_channel->scaling_factor /= FREQUENCY;
    }

    switch (work_note->effect_number)
    {
        /* Set volume. */

        case 0xC:
        {
            console.cursor_move (0, 24);
            console.print_formatted ("Effect C: Parameter = %x  ",
                                     work_note->effect_parameter);
      
            work_channel->volume = work_note->effect_parameter;
            if (work_channel->volume > 0x40)
            {
                work_channel->volume = 0x40;
            }

            break;
        }

        /* Next pattern. */

        case 0xD:
        {
            current_pattern++;
            current_row = 0;

            /* FIXME: Should jump to right note also */

            break;
        }

        /* Set speed/BPM. */

        case 0xF:
        {
            console.cursor_move (0, 25);
            console.print_formatted ("Effect F: Parameter = %x  ",
                                     work_note->effect_parameter);

            if (work_note->effect_parameter < 0x20)
            {
                /* Speed. */
                speed = work_note->effect_parameter;
            }
            else
            {
                /* BPM. */
                bpm = work_note->effect_parameter;
            }

            tick_length = speed * ((FREQUENCY * 5) / bpm) >> 1;

            break;
        }
    }
}


