# $chaos: makefile,v 1.13 2002/06/15 10:59:47 per Exp $

# Abstract: storm G3 makefile
# Authors: Henrik Hallin <hal@chaosdev.org>
#          Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

OBJECTS = cpu.o debug.o dispatch.o dma.o exception.o \
exception_lowlevel.o gdb.o  idt.o init.o irq.o irq_handlers.o main.o \
memory_global.o memory_physical.o memory_virtual.o multiboot.o

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
