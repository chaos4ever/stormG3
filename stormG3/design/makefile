# $chaos: makefile,v 1.4 2002/05/28 07:03:38 per Exp $

# Abstract: storm G3 design makefile
# Author: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

DOC=stormG3
MAIN=$(DOC).xml
SECTS=license.xml memory_management.xml module.xml goals.xml process.xml \
stdint.xml
SRC=$(MAIN) $(SECTS)
PNGS=memory_map.png

all: $(DOC).pdf $(DOC).txt $(DOC).rtf $(DOC)

$(DOC).pdf: $(SRC)
	jw -b pdf $(MAIN)

$(DOC).txt: $(SRC)
	jw -b txt $(MAIN)

$(DOC).rtf: $(SRC)
	jw -b rtf $(MAIN)

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
