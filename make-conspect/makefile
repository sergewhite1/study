all: ques_02 make-conspect.pdf 

make-conspect.pdf: make-conspect.tex preamble.tex
	pdflatex $<
	@echo Second run to resolve references
	pdflatex $<

.PHONY: ques_02_clean
ques_02_clean:
	@echo Deleting old files...
	@rm -fv projects/ques_02/ques_exe
	@rm -fv projects/ques_02/ques_ut
	@rm -fv projects/ques_02/*.c
	@rm -fv projects/ques_02/*.h
	@rm -fv projects/ques_02/*.o

.PHONY: ques_02
ques_02: ques_02_clean
	@echo Deleting old files...
	@rm -fv projects/ques_02/ques_exe
	@rm -fv projects/ques_02/ques_ut
	@rm -fv projects/ques_02/*.c
	@rm -fv projects/ques_02/*.h
	@echo Copying necessary files from ques_01...
	@cp -v projects/ques_01/*.c projects/ques_02/
	@cp -v projects/ques_01/*.h projects/ques_02/

.PHONY: clean
clean: ques_02_clean
	rm -v *.aux *.log *.out *.pdf *.synctex.gz
