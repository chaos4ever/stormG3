# $chaos: storm.make,v 1.3 2002/05/26 20:08:23 per Exp $

# Abstract: storm G3 makefile
# Authors: Henrik Hallin <hal@chaosdev.org>
#          Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

# Settings.
# CC = i686-storm-chaos-gcc
INCLUDES = -I$(BUILD_ROOT)/include
DEFINES = -DSTORM -DCREATOR=\"`whoami`@`hostname`\"
CFLAGS = -Wall -W -Wshadow -Wpointer-arith -Waggregate-return \
-Wstrict-prototypes -Wredundant-decls -Winline -Wmissing-prototypes \
-Werror -Wcast-align -Wbad-function-cast -Wsign-compare \
-Wmissing-declarations -pipe -Wnested-externs \
-O3 -fno-builtin -funsigned-char -g -fomit-frame-pointer \
-ffreestanding $(EXTRA_CFLAGS) $(DEFINES) $(INCLUDES)
LDFLAGS = -nostdlib -Wl,-T,kernel.ld $(EXTRA_LDFLAGS)
INSTALL_PATH=/tftpboot

# Programs.
INSTALL = install

.PHONY: all clean install 

clean::
	rm -f $(OBJECTS)

%.o: %.c
	$(CC) -c $< -o $(@) $(CFLAGS)
	@$(CC) -M $< $(CFLAGS) $(INCLUDES) $(DEFS) > $(*F).dep

%.o: %.S
	$(CC) -c $< -o $(@) $(CFLAGS)
	@$(CC) -M $< $(CFLAGS) $(INCLUDES) $(DEFS) > $(*F).dep

-include $(shell echo *.dep)
