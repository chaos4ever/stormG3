# $chaos: makefile,v 1.1 2002/06/20 19:54:20 per Exp $

# Abstract: Log library makefile.
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.
# Use freely under the terms listed in the file COPYING.

HEADERS = log.h

all:

clean::

install: all
	$(INSTALL) -d $(INSTALL_PATH)/data/programming/c/headers/log
	for e in $(HEADERS) ; \
        do $(INSTALL) $$e $(INSTALL_PATH)/data/programming/c/headers/log ; \
	done

include $(BUILD_ROOT)/libraries.make
