# $chaos: makefile,v 1.2 2002/06/17 18:55:16 per Exp $

# Abstract: storm G3 makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

HEADERS = memory.h port.h

install:
	install -d $(INSTALL_PATH)/data/programming/c/headers/storm/ia32
	for e in $(HEADERS) ; do \
        install $$e $(INSTALL_PATH)/data/programming/c/headers/storm/ia32 ; \
        done

include $(BUILD_ROOT)/storm.make

