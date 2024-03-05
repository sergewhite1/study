DEPS = latex.tex preamble.tex titlepage.tex

latex.pdf: $(DEPS) 
	pdflatex $<
 
latex.dvi: $(DEPS)
	latex $<

.PHONY: clean
clean:
	rm -fv *.aux *.dvi *.log *.pdf
