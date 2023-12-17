all:

.PHONY: CREATE_DIR
CREATE_DIR:
	mkdir -p out
	mkdir -p out/src

ARGS= -c -I. -g -Wall -Wpedantic

out/program: out/src/main.o         \
             out/src/target.o       \
             out/src/time_service.o
	g++ -o $@ $^
	$@

out/src/main.o: src/main.cpp             \
                interface/target.h       \
                interface/time_service.h
	g++ $(ARGS) -o $@ $<

out/src/target.o: src/target.cpp     \
                  interface/target.h \
				  interface/time_service.h
	g++ $(ARGS) -o $@ $<

out/src/time_service.o: src/time_service.cpp \
                        interface/time_service.h
	g++ $(ARGS) -o $@ $<

out/ut: out/ut.o         \
        out/src/target.o \
		out/src/time_service.o
	g++ -o $@ $^
	$@

out/ut.o: ut/ut.cpp
	g++ $(ARGS) -o $@ $<

all: CREATE_DIR out/ut out/program

.PHONY: clean
clean:
	rm -rv out
