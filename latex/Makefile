DEPS := latex.tex
DEPS := $(DEPS) $(shell ls *.tex)
DEPS := $(DEPS) $(shell find section  -name '*.tex')
DEPS := $(DEPS) $(shell find appendix -name '*.tex')

latex.pdf: $(DEPS)
	@# Need 2 runs. The first run will produce toc file (Table Of Contents)
	pdflatex $<
	pdflatex $<
 
latex.dvi: $(DEPS)
	@# Need 2 runs. The first run will produce toc file (Table Of Contents)
	latex $<
	latex $<

.PHONY: clean
clean:
	rm -fv *.aux *.dvi *.log *.out *.pdf *.synctex.gz *.toc
	rm -fv section/*.log
