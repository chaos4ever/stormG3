# $chaos$

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

include $(BUILD_ROOT)/storm.make
