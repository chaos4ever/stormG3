# $chaos: makefile,v 1.1 2002/06/16 21:07:58 per Exp $

# Abstract: Modules makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.
# Use freely under the terms listed in the file COPYING.

BUILD_ROOT = $(CURDIR)
export BUILD_ROOT
SUBDIRS = keyboard

all:
	for e in $(SUBDIRS) ; do \
	make -C $$e ; \
        done

clean::
	for e in $(SUBDIRS) ; do \
	make -C $$e clean ; \
        done

install:
	install -d $(INSTALL_PATH)/system/modules
	for e in $(SUBDIRS) ; do \
	make -C $$e install ; \
        done

include $(BUILD_ROOT)/modules.make
