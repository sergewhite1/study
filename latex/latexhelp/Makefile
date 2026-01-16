all: out_dir validate_json out/main/latexhelp.pdf out/example/latexhelp_example.pdf

.PHONY: out_dir
out_dir:
	mkdir -p out/main
	mkdir -p out/example

.PHONY: validate_json
validate_json:
	python3 -mjson.tool latexhelp.json > /dev/null
	python3 -mjson.tool example/latexhelp_example.json > /dev/null

out/main/latexhelp.pdf: out/main/latexhelp.tex
	pdflatex -output-directory out/main $<

out/main/latexhelp.tex: latexhelp.py latexhelp.json
	python3 latexhelp.py --out $@

out/example/latexhelp_example.pdf: out/example/latexhelp_example.tex
	pdflatex -output-directory out/example $<

out/example/latexhelp_example.tex: latexhelp.py example/latexhelp_example.json
	python3 latexhelp.py --db example/latexhelp_example.json --out $@

.PHONY: clean
clean:
	rm -rf out

.PHONY: analyze-python-code
analyze-python-code:
	flake8

.PHONY: compare-example-tex
compare-example-tex:
	diff example/latexhelp_example.tex out/example/latexhelp_example.tex