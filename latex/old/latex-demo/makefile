document.pdf: document.tex preamble.tex \
              img/picture.png
	pdflatex $<

.PHONY: clean
clean:
	rm -v *.aux *.log *.out *.pdf
