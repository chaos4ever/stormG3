# $chaos: makefile,v 1.2 2002/05/27 19:08:02 per Exp $

# Abstract: storm G3 makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

HEADERS = config.h defines.h magic_cookies.h queue.h return_value.h types.h

install:
	install -d $(INSTALL_PATH)/data/programming/c/headers/storm
	for e in $(HEADERS) ; do \
        install $$e $(INSTALL_PATH)/data/programming/c/headers/storm ; \
        done

include $(BUILD_ROOT)/storm.make
