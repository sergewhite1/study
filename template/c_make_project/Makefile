CC=gcc
CFLAGS=-c -Wall
EXECUTABLE=hello

$(EXECUTABLE): main.o
	$(CC) main.o -o $(EXECUTABLE)

main.o: main.c
	$(CC) $(CFLAGS)  main.c -o main.o

clean:
	rm -v *.o
	rm -v $(EXECUTABLE)
