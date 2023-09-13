set -x

gcc -c main.c -o main.o
gcc -c ques.c -o ques.o

gcc -c ut.c -o ut.o
gcc -c ques_ut.c -o ques_ut.o
gcc ques_ut.o ut.o ques.o -lm -o ques_ut

./ques_ut

gcc main.o ques.o  -lm -o ques_exe

