# $chaos$

# Abstract: storm G3 design makefile
# Author: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

DOC=stormG3
MAIN=$(DOC).xml
SECTS=memory_management.xml license.xml
SRC=$(MAIN) $(SECTS)
PNGS=memory_map.png

all: $(DOC).pdf $(DOC).ps $(DOC)

$(DOC).pdf: $(SRC)
	jw -b pdf $(MAIN)

$(DOC).ps: $(SRC)
	jw -b ps $(MAIN)

$(DOC): $(SRC)
	-rm -rf $@
	jw -b html -o $(@) $(MAIN)
	cp $(PNGS) $(@)

clean:
	-$(RM) *.log *.dvi *.aux *.tex *.sed *.out *-t
	-$(RM) *.html
	-$(RM) -r $(DOC) $(DOC).ps $(DOC).pdf $(DOC).fo

distclean: clean
	-$(RM) *~
	-$(RM) -r docbook

.PHONY: distclean clean all
