# $chaos: makefile,v 1.1 2002/10/21 21:34:46 per Exp $

# Abstract: System Security Overview makefile
# Author: Per Lundberg <per@chaosdev.org>

# Copyright 2002 chaos development.

DOC = system_security_overview
MAIN = $(DOC).xml
STYLESHEET = custom.dsl
SECTIONS = implementation.xml introduction.xml problem.xml solution.xml \
           systems.xml
CSS = system_security_overview.css
SRC = $(MAIN) $(CSS) $(STYLESHEET) $(SECTIONS)
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
	jw -d $(STYLESHEET) -b html -o $(@) $(MAIN)
#	cp $(PNGS) $(@)
	cp $(CSS) $(@)

clean:
	-$(RM) *.log *.dvi *.aux *.tex *.sed *.out *-t
	-$(RM) *.html
	-$(RM) -r $(DOC) $(DOC).ps $(DOC).pdf $(DOC).fo

distclean: clean
	-$(RM) *~
	-$(RM) -r docbook

.PHONY: distclean clean all
