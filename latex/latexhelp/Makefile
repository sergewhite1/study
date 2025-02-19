all: out_dir out/latexhelp.pdf

.PHONY: out_dir
out_dir:
	mkdir -p out

out/latexhelp.pdf: out/latexhelp.tex
	pdflatex -output-directory out $<

out/latexhelp.tex: latexhelp.py latexhelp.json
	python3 latexhelp.py

.PHONY: clean
clean:
	rm -rf out