MAIN_FILE = latex.tex

SECTION = section/why_latex.tex     \
          section/struct_of_doc.tex \
          section/about_preamble.tex      \
          section/about_titlepage.tex    \
          section/about_toc.tex           \
          section/about_appendix.tex      \
          section/about_thebibliography.tex

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
	rm -fv *.aux *.dvi *.log *.out *.pdf *.synctex.gz *.toc
	rm -fv section/*.log
