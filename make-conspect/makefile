make-conspect.pdf: make-conspect.tex preamble.tex
	pdflatex $<
	@echo Second run to resolve references
	pdflatex $<

.PHONY: clean
clean:
	rm -v *.aux *.log *.out *.pdf *.synctex.gz
