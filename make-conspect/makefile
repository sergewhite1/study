all: make-conspect.pdf qes_02

make-conspect.pdf: make-conspect.tex preamble.tex
	pdflatex $<
	@echo Second run to resolve references
	pdflatex $<

.PHONY: qes_02
qes_02:
	cd projects
	rm -f qes_02/*.c
	cd ..

.PHONY: clean
clean:
	rm -v *.aux *.log *.out *.pdf *.synctex.gz
