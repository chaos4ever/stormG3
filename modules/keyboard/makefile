# $chaos: makefile,v 1.2 2002/06/17 22:50:37 per Exp $

# Abstract: Keyboard module makefile.
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

OBJECTS = controller.o init.o keyboard.o mouse.o
BINARY = keyboard.so

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
