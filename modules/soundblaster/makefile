# $chaos: makefile,v 1.4 2002/06/18 22:19:18 per Exp $

# Abstract: Soundblaster module makefile.
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.
# Use freely under the terms listed in the file COPYING.

OBJECTS = soundblaster.o
BINARY = soundblaster.so

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
