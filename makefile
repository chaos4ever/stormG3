# $Id$
# Abstract: Top-level chaos makefile
# Author: Per Lundberg <plundis@chaosdev.org>

# Copyright 1998-2000 chaos development.

ROOT=/mnt/chaos
DIRECTORES=system system/kernel system/servers data data/programming data/programming/c data/programming/c/headers

.PHONY:	all install clean snapshot autochaos configure

all:
	$(MAKE) -C storm
	$(MAKE) -C libraries
	$(MAKE) -C servers
	$(MAKE) -C programs

install-storm: configure-storm
	$(MAKE) -C storm install

install-libraries: configure-libraries
	$(MAKE) -C libraries install

install-servers: configure-servers
	$(MAKE) -C servers install

install-programs: configure-programs
	$(MAKE) -C programs install

directories:
	for e in $(DIRECTORES) ; do if ! [ -e "$(ROOT)/$$e" ] ; then mkdir $(ROOT)/$$e ; fi ; done

install: directories install-storm install-libraries install-servers install-programs

autochaos:
	cd storm && autochaos
	$(MAKE) -C libraries autochaos
	$(MAKE) -C servers autochaos
	$(MAKE) -C programs autochaos

configure: configure-storm configure-libraries configure-servers configure-programs

configure-storm:
	cd storm && ./configure
	touch configure-storm

configure-libraries:
	$(MAKE) -C libraries configure
	touch configure-libraries

configure-servers:
	$(MAKE) -C servers configure
	touch configure-servers

configure-programs:
	$(MAKE) -C programs configure
	touch configure-programs

clean:
	$(MAKE) -C storm clean
	$(MAKE) -C libraries clean
	$(MAKE) -C servers clean
	$(MAKE) -C programs clean
	find . -type f -name .deps -exec rm -rf {} ';'
	find . -type f -name \*~ -exec rm {} ';'
	find . -type f -name \*.dep -exec rm {} ';'
	find . -type f -name .#\* -exec rm {} ';'

clean-all: clean
	rm -f configure-storm configure-libraries configure-servers configure-programs

snapshot:
	cd ../ && tar -c --exclude CVS --exclude contributed -vIf chaos_snapshot-$$(date +%Y%m%d).tar.bz2 chaos
