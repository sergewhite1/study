all: out_dir out/latexhelp_alph.pdf

.PHONY: out_dir
out_dir:
	mkdir -p out

out/latexhelp_alph.pdf: out/latexhelp_alph.tex
	pdflatex -output-directory out $<

out/latexhelp_alph.tex: latexhelp.py latexhelp.json
	python3 latexhelp.py

.PHONY: clean
clean:
	rm -rf out