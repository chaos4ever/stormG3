# $chaos: makefile,v 1.5 2002/06/20 21:25:15 per Exp $

# Abstract: Libraries makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.
# Use freely under the terms listed in the file COPYING.

BUILD_ROOT = $(CURDIR)
export BUILD_ROOT
SUBDIRS = log

all:
	for e in $(SUBDIRS) ; do \
	make -C $$e || exit ; \
        done

clean::
	for e in $(SUBDIRS) ; do \
	make -C $$e clean || exit ; \
        done

install:
	for e in $(SUBDIRS) ; do \
	make -C $$e install || exit ; \
        done

include $(BUILD_ROOT)/libraries.make
