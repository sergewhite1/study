DEPS := latex.tex
DEPS := $(DEPS) $(shell ls *.tex)
DEPS := $(DEPS) $(shell find section  -name '*.tex')
DEPS := $(DEPS) $(shell find appendix -name '*.tex')

OUTDIR = out

$(OUTDIR)/latex.pdf: $(DEPS) | $(OUTDIR)
	@# Need 2 runs. The first run will produce toc file (Table Of Contents)
	pdflatex -output-directory $(OUTDIR) $<
	pdflatex -output-directory $(OUTDIR) $<

latex.dvi: $(DEPS)
	@# Need 2 runs. The first run will produce toc file (Table Of Contents)
	latex $<
	latex $<

$(OUTDIR):
	mkdir $(OUTDIR)

.PHONY: clean
clean:
	rm -rfv *.aux *.dvi *.log *.out *.pdf *.synctex.gz *.toc section/*.log $(OUTDIR)