# $chaos: makefile,v 1.1 2002/05/25 20:10:01 per Exp $

# Abstract: storm G3 makefile
# Authors: Henrik Hallin <hal@chaosdev.org>
#          Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

BUILD_ROOT = $(CURDIR)
export BUILD_ROOT
SUBDIRS = source

all:
	$(MAKE) -C source 

clean::
	$(MAKE) -C source clean

install:
	$(MAKE) -C source install
	$(MAKE) -C include install

include $(BUILD_ROOT)/storm.make
