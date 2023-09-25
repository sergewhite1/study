ques_exe: main.o ques.o
	gcc main.o ques.o -lm -o ques_exe

main.o: main.c ques.h
	gcc -c main.c -o main.o

ques.o: ques.c ques.h
	gcc -c ques.c -o ques.o

clean:
	rm -fv ques_exe *.o
