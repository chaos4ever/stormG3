# $chaos: makefile,v 1.4 2002/06/20 19:54:19 per Exp $

# Abstract: Modules makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.
# Use freely under the terms listed in the file COPYING.

BUILD_ROOT = $(CURDIR)
export BUILD_ROOT
SUBDIRS = log keyboard soundblaster

all:
	for e in $(SUBDIRS) ; do \
	make -C $$e || exit ; \
        done

clean::
	for e in $(SUBDIRS) ; do \
	make -C $$e clean || exit ; \
        done

install:
	install -d $(INSTALL_PATH)/system/modules
	for e in $(SUBDIRS) ; do \
	make -C $$e install || exit ; \
        done

include $(BUILD_ROOT)/modules.make
