# $chaos: makefile,v 1.1 2002/05/25 20:10:01 per Exp $

# Abstract: storm G3 makefile
# Authors: Henrik Hallin <hal@chaosdev.org>
#          Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

GENERIC_OBJECTS = avltree.o queue.o
GENERIC_LIB = libgeneric.a

all: $(GENERIC_LIB) $(GENERIC_OBJECTS)
	$(MAKE) -C ia32

$(GENERIC_LIB): $(GENERIC_OBJECTS)
	ar r $(@) $(GENERIC_OBJECTS)

clean::
	$(MAKE) -C ia32 clean

install:
	$(MAKE) -C ia32 install

include $(BUILD_ROOT)/storm.make
