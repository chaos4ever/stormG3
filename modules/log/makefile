# $chaos: makefile,v 1.1 2002/06/18 22:30:14 per Exp $

# Abstract: Log module makefile.
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.
# Use freely under the terms listed in the file COPYING.

OBJECTS = log.o
BINARY = log.so

all: $(BINARY)

clean::
	rm -f $(BINARY) $(OBJECTS)

install: all
	$(INSTALL) $(BINARY) $(INSTALL_PATH)/system/modules
	strip $(INSTALL_PATH)/system/modules/$(BINARY)
	gzip -9f $(INSTALL_PATH)/system/modules/$(BINARY)

main.o:
	$(CC) -o $(@) -c $< $(CFLAGS)

$(BINARY): $(OBJECTS)
	$(LD) -o $(@) --shared $(OBJECTS) $(LDFLAGS)

include $(BUILD_ROOT)/modules.make
