all: out_dir out/main/latexhelp.pdf out/example/latexhelp_example.pdf

.PHONY: out_dir
out_dir:
	mkdir -p out/main
	mkdir -p out/example

out/main/latexhelp.pdf: out/main/latexhelp.tex
	pdflatex -output-directory out/main $<

out/main/latexhelp.tex: latexhelp.py latexhelp.json
	python3 latexhelp.py

out/example/latexhelp_example.pdf: out/example/latexhelp_example.tex
	@echo STUB

out/example/latexhelp_example.tex: latexhelp.py latexhelp_example.json
	python3 latexhelp.py --db latexhelp_example.json --out $@

.PHONY: clean
clean:
	rm -rf out