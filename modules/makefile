# $chaos: makefile,v 1.2 2002/06/18 22:19:17 per Exp $

# Abstract: Modules makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.
# Use freely under the terms listed in the file COPYING.

BUILD_ROOT = $(CURDIR)
export BUILD_ROOT
SUBDIRS = keyboard soundblaster

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
