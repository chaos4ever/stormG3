# $chaos: makefile,v 1.5 2002/06/04 18:34:32 per Exp $

# Abstract: System Security Overview makefile
# Author: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

DOC = system_security_overview
MAIN = $(DOC).xml
SECTIONS = introduction.xml systems.xml problem.xml solution.xml
SRC = $(MAIN) $(SECTIONS)
PNGS =
WEBROOT = /var/webroot/web.chaosdev.org

# You should not need to change anything below this.

.PHONY: install
all: $(DOC).pdf $(DOC).txt $(DOC).rtf $(DOC)

install: $(DOC)
	rm -rf $(WEBROOT)/$(DOC)
	cp -r $(DOC) $(WEBROOT)

$(DOC).pdf: $(SRC)
	jw -b pdf $(MAIN)

$(DOC).txt: $(SRC)
	jw -b txt $(MAIN)

$(DOC).rtf: $(SRC)
	jw -b rtf $(MAIN)

$(DOC): $(SRC)
	-rm -rf $@
	jw -b html -o $(@) $(MAIN)
#	cp $(PNGS) $(@)

clean:
	-$(RM) *.log *.dvi *.aux *.tex *.sed *.out *-t
	-$(RM) *.html
	-$(RM) -r $(DOC) $(DOC).ps $(DOC).pdf $(DOC).fo

distclean: clean
	-$(RM) *~
	-$(RM) -r docbook

.PHONY: distclean clean all
