# $chaos: makefile,v 1.7 2002/06/11 21:26:39 per Exp $

# Abstract: storm G3 makefile
# Authors: Henrik Hallin <hal@chaosdev.org>
#          Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

OBJECTS = debug.o dma.o exception.o init.o main.o memory_global.o \
memory_physical.o memory_virtual.o multiboot.o

BINARY = stormG3
.PHONY: main.o

all: $(BINARY)

clean::
	rm -f $(BINARY)

install: all
	$(INSTALL) $(BINARY) $(INSTALL_PATH)/system/kernel
	gzip -9f $(INSTALL_PATH)/system/kernel/$(BINARY)

main.o:
	$(CC) -o $(@) -c $< $(CFLAGS)

$(BINARY): $(OBJECTS)
	$(CC) -o $(@) $(OBJECTS) -L.. -lgeneric $(LDFLAGS)

include $(BUILD_ROOT)/storm.make
