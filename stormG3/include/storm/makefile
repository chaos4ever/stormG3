# $chaos: makefile,v 1.1 2002/06/15 10:55:38 per Exp $

# Abstract: storm G3 makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

HEADERS = module.h return_value.h storm.h types.h

install:
	install -d $(INSTALL_PATH)/data/programming/c/headers/storm
	for e in $(HEADERS) ; do \
        install $$e $(INSTALL_PATH)/data/programming/c/headers/storm ; \
        done

include $(BUILD_ROOT)/storm.make
