MAIN_FILE = latex.tex

SECTION = section/01_why_latex.tex     \
          section/02_struct_of_doc.tex \
          section/03_preamble.tex      \
          section/04_title_page.tex

APPENDIX = appendix/appendix-1.tex \
           appendix/appendix-2.tex

DEPS = $(MAIN_FILE) preamble.tex titlepage.tex thebibliography.tex $(SECTION) $(APPENDIX)

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
	rm -fv *.aux *.dvi *.log *.pdf *.synctex.gz *.toc
	rm -fv section/*.log
