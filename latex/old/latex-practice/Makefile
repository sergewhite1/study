.PHONY: ALL
ALL: p1.pdf l.pdf

cmd=pdflatex

p1.pdf: p1.tex preamble.tex 
	# Call pdflatex twice for table of content
	$(cmd) $<
	$(cmd) $<

l.pdf: l.tex preamble.tex 
	$(cmd) $<

.PHONY: clean
clean:
	rm -v *.aux *.log *.pdf *.toc
