# $chaos: makefile,v 1.2 2002/06/17 18:55:16 per Exp $

# Abstract: storm G3 makefile
# Authors: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

HEADERS = defines.h module.h return_value.h storm.h types.h

install:
	$(MAKE) -C ia32 install
	install -d $(INSTALL_PATH)/data/programming/c/headers/storm
	for e in $(HEADERS) ; do \
        install $$e $(INSTALL_PATH)/data/programming/c/headers/storm ; \
        done

include $(BUILD_ROOT)/storm.make
