a.out: main.o
	g++ main.o
main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -v *.o
	rm a.out
