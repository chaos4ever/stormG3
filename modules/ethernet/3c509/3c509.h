/* $chaos: 3c509.h,v 1.1 2002/07/28 11:21:49 johannes Exp $ */
/* Abstract: Headerfile for the 3c509 module. */
/* Author: Johannes Lundberg <jojo@chaosdev.org>
           Håkan Larsson     <trc@chaosdev.org> */

/* Copyright 2002 chaos development. */
/* Use freely under the terms listed in the file LICENSE. */

#ifndef __3C509_H__
#define __3C509_H__

return_t probe (void);

/* Command Register Commands. */

#define GLOBAL_RESET                0x0000
#define SELECT_REGISTER_WINDOW      0x0800
#define SELECT_COAXIAL_TRANSCEIVER  0x1000

#define RX_DISABLE                  0x1800
#define RX_ENABLE 		    0x2000
#define RX_RESET                    0x2800
#define RX_DISCARD_TOP_PACKET       0x4000

#define TX_ENABLE                   0x4800
#define TX_DISABLE                  0x5000
#define TX_RESET                    0x5800

#define REQUEST_INTERRUPT           0x6000
#define ACKNOWLEDGE_INTERRUPT       0x6800

/*
0000 1000 0000 0000

1001 1000 0000 0001 = 0x9801
0001 0000 0000 0001 = 0x1001

port_out_uint16 (SELECT_REGISTER_WINDOW | 4);
*/

#endif /* __3C509_H__ */
