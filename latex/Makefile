MAIN_TARGET_BASE_NAME = osr
OUTDIR = out
LATEX = pdflatex

DEPS := latex.tex
DEPS := $(DEPS) $(shell find tex  -name '*.tex')

CLEAN_FILES := $(OUTDIR)

$(OUTDIR)/$(MAIN_TARGET_BASE_NAME).pdf: $(DEPS) | $(OUTDIR)
	# Twice run for reference resolving
	$(LATEX) -output-directory $(OUTDIR) $<
	$(LATEX) -output-directory $(OUTDIR) $<

latex.dvi: $(DEPS)
	# Twice run for reference resolving
	latex $<
	latex $<

$(OUTDIR):
	mkdir $(OUTDIR)

.PHONY: clean
clean:
	rm -rfv $(CLEAN_FILES)

.PHONY: print_deps
print_deps:
	@echo DEPS=$(DEPS)
