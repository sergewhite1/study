CC=g++
CFLAGS=-c -Wall
EXECUTABLE=hello

$(EXECUTABLE): main.o
	$(CC) main.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) $(CFLAGS)  main.cpp -o main.o

clean:
	rm -v *.o
	rm -v $(EXECUTABLE)
