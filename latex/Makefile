MAIN_FILE = latex.tex
APPENDIX = appendix-1.tex appendix-2.tex
DEPS = $(MAIN_FILE) preamble.tex titlepage.tex thebibliography.tex $(APPENDIX)

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
	rm -fv *.aux *.dvi *.log *.pdf *.toc
