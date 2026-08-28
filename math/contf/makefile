MAIN_TARGET_BASE_NAME = cont_sin
OUTDIR=out
LATEX = pdflatex
BIBTEX = bibtex

DEPS := $(MAIN_TARGET_BASE_NAME).tex
DEPS := $(DEPS) bib.bib

CLEAN_FILES := $(OUTDIR)

$(OUTDIR)/$(MAIN_TARGET_BASE_NAME).pdf: $(DEPS) | $(OUTDIR)
	$(LATEX) -output-directory $(OUTDIR) $<
	$(BIBTEX) $(basename $@).aux
	$(LATEX) -output-directory $(OUTDIR) $<
	$(LATEX) -output-directory $(OUTDIR) $<

$(OUTDIR):
	mkdir $(OUTDIR)

.PHONY: clean
clean:
	rm -frv $(CLEAN_FILES)

.PHONY: print_deps
print_deps:
	@echo DEPS=$(DEPS)
