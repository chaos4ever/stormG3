# $Id$

# This file is used for starting gdb with our binary loaded (very handy
# for debugging the kernel over a serial line).
set remotebaud 115200
target remote /dev/ttyS0
