/* $chaos: dotfile.emacs,v 1.43 2002/11/14 20:15:09 per Exp $ */
/* Abstract: Header file for modplay. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

/**
 * @file             modplay.h
 * @brief            Header file for modplay
 */

#ifndef __MODPLAY_H__
#define __MODPLAY_H__

/* Defines. */
#define BUFFER_SIZE     2000
#define FREQUENCY       22000
#define CHANNELS        4
#define ROWS            64
#define BYTES_PER_PATTERN \
                        ROWS*CHANNELS*4
//#define PAL 3546894
#define PAL             0x361F0E00     /* 3546894 << 2 */
#define PROGRAM_NAME    "modplay"

/* Structures. */
typedef struct
{
    uint8_t name[20];
    uint8_t song_length;
    uint8_t play_sequence[128];
    uint8_t id[4];
    unsigned int physical_patterns;
} module_type;

module_type module;

typedef struct
{
    uint8_t name[22];
    uint16_t length;
    uint8_t finetune;
    uint8_t volume;
    uint16_t repeat_point;
    uint16_t repeat_length;
    uint8_t *data;
} sample_type;

typedef struct
{
    unsigned int sample_number;
    uint16_t length;
    uint8_t finetune;
    uint8_t volume;
    uint16_t repeat_point;
    uint16_t repeat_length;
    uint32_t scaling_factor;
    uint8_t *sample_data;
    uint16_t period_frequency;
    uint32_t ticks;
} channel_type;

typedef struct
{
    uint8_t sample_number : 8;
    uint16_t period_frequency : 12;
    uint8_t effect_number : 4;
    uint8_t effect_parameter : 8;
} note_type PACKED;

/* Functions. */
void fill_buffer (uint8_t *buffer);
void load_module (void);
void do_note (note_type *work_note, channel_type *work_channel);

#endif /* !__MODPLAY_H__ */
