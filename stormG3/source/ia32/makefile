# $chaos: makefile,v 1.1 2002/05/25 20:09:40 per Exp $

# Abstract: storm G3 makefile
# Authors: Henrik Hallin <hal@chaosdev.org>
#          Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

OBJECTS = debug.o init.o main.o multiboot.o
BINARY = storm

all: $(BINARY)

clean::
	rm -f $(BINARY)

install: all
	$(INSTALL) $(BINARY) $(INSTALL_PATH)/system/kernel

$(BINARY): $(OBJECTS)
	$(CC) -o $(@) $(OBJECTS) -L.. -lgeneric $(LDFLAGS)

include $(BUILD_ROOT)/storm.make
