/* $chaos: xemacs-script,v 1.5 2002/05/23 11:22:14 per Exp $ */
/* Abstract: Timer support. */
/* Author: Per Lundberg <per@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file COPYING. */

#ifndef __STORM_IA32_TIMER_H__
#define __STORM_IA32_TIMER_H__

/* Defines. */
/* Port numbers. */
#define PIT_BASE                0x40
#define PIT_CHANNEL_0           (PIT_BASE + 0)
#define PIT_COUNTER_DIVISOR     (PIT_BASE + 0)
#define PIT_COUNTER_1           (PIT_BASE + 1)
#define PIT_RAM_REFRESH_COUNTER (PIT_BASE + 1)
#define PIT_COUNTER_2           (PIT_BASE + 2)
#define PIT_MODE_PORT           (PIT_BASE + 3)

/* Bit fields in the mode control word. */
#define COUNTER_0_SELECT        (0)
#define COUNTER_1_SELECT        (BIT_VALUE (6))
#define COUNTER_2_SELECT        (BIT_VALUE (7))
#define READ_BACK_COUNTER       (BIT_VALUE (7) | BIT_VALUE (6))

/* The following are used when READ_BACK_COUNTER is clear. */
#define COUNTER_LATCH_COMMAND   (0)
#define ACCESS_LOW_COUNTER_U8   (BIT_VALUE (4))
#define ACCESS_HIGH_COUNTER_U8  (BIT_VALUE (5))

/* Zero detection interrupt. */
#define MODE_0_SELECT           (0)

/* Programmable one shot. */
#define MODE_1_SELECT           (BIT_VALUE (1))

/* Rate generator. */
#define MODE_2_SELECT           (BIT_VALUE (2))

/* Square wave generator. */
#define MODE_3_SELECT           (BIT_VALUE (2) | BIT_VALUE (1))

/* Software triggered strobe. */
#define MODE_4_SELECT           (BIT_VALUE (3))

/* Hardware triggered strobe. */
#define MODE_5_SELECT           (BIT_VALUE (3) | BIT_VALUE (1))

/* 16-bit binary counter. */
#define BINARY_COUNTER          (0)

/* The clock speed of the timer chip. */
#define CLOCK_TICK_RATE         1193180

/* Used for setting counter divisors. The 8254 chip has a fixed
   frequency of 1193180 Hz, one fourth of the original 8088 speed. So,
   when we want a given speed, we divide this frequency with the
   desired frequency. */
#define COUNTER_DIVISOR(hz)     (CLOCK_TICK_RATE / hz)

/* Function prototypes. */
/* Initialize the timer. */
extern void timer_init (void);

/* External variables. */
extern unsigned int hz;

#endif /* !__STORM_IA32_TIMER_H__ */
