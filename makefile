# $Id$
# Abstract: Top-level chaos makefile
# Authors: Henrik Hallin <hal@chaosdev.org>
#          Per Lundberg <per@chaosdev.org>

# Copyright 1998-2000 chaos development.

# Installation root. Change this if you want to install to a specific location.
# Default is to install to the location of the source, but
# you may like to install directly to a mounted chaos partition or something.

INSTALL_PATH=$$(pwd)/root

.PHONY:	all install clean snapshot autochaos configure

all:
	$(MAKE) -C storm install
	$(MAKE) -C libraries install
	$(MAKE) -C servers install
	$(MAKE) -C programs install

configure:
	@export CHAOS_INSTALL_PATH=$(INSTALL_PATH)
	cd storm && ./configure --install-prefix $$CHAOS_INSTALL_PATH
	$(MAKE) -eC libraries configure
	$(MAKE) -eC servers configure
	$(MAKE) -eC program configure

# This one is used for building a fresh source tree.

build:
	@export CHAOS_INSTALL_PATH=$(INSTALL_PATH)
	@ln -sf storm/ia32 storm/current-arch
	@ln -sf storm/include/storm/ia32 storm/include/storm/current-arch
	cd storm && ./configure --install-prefix $$CHAOS_INSTALL_PATH
	$(MAKE) -C storm install
	$(MAKE) -eC libraries configure
	$(MAKE) -C libraries install
	$(MAKE) -eC servers configure
	$(MAKE) -C servers install
	$(MAKE) -eC programs configure
	$(MAKE) -C programs install

autochaos:
	cd storm && autochaos
	$(MAKE) -C libraries autochaos
	$(MAKE) -C servers autochaos
	$(MAKE) -C programs autochaos

clean:
	$(MAKE) -C storm clean
	$(MAKE) -C libraries clean
	$(MAKE) -C servers clean
	$(MAKE) -C programs clean
	find . -type f -name .deps -exec rm -rf {} ';'
	find . -type f -name \*~ -exec rm {} ';'
	find . -type f -name \*.dep -exec rm {} ';'
	find . -type f -name .#\* -exec rm {} ';'

snapshot:
	cd ../ && tar -c --exclude CVS --exclude contributed -vIf chaos_snapshot-$$(date +%Y%m%d).tar.bz2 chaos
