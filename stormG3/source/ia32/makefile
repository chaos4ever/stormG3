# $chaos: makefile,v 1.3 2002/06/05 17:49:07 per Exp $

# Abstract: storm G3 makefile
# Authors: Henrik Hallin <hal@chaosdev.org>
#          Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

OBJECTS = debug.o init.o main.o memory_physical.o multiboot.o
BINARY = stormG3

all: $(BINARY)

clean::
	rm -f $(BINARY)

install: all
	$(INSTALL) $(BINARY) $(INSTALL_PATH)/system/kernel

$(BINARY): $(OBJECTS)
	$(CC) -o $(@) $(OBJECTS) -L.. -lgeneric $(LDFLAGS)

include $(BUILD_ROOT)/storm.make
