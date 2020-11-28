CC=g++
CFLAGS= -O0 -Wall
EXECUTABLE=hello

$(EXECUTABLE): main.o
	$(CC) main.o -o $(EXECUTABLE)

main.o: main.cpp
	$(CC) -S $(CFLAGS) main.cpp 
	$(CC) -c main.s -o main.o

clean:
	rm -v *.s
	rm -v *.o
	rm -v $(EXECUTABLE)
