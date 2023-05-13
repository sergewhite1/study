set -x

gcc -c main.c -o main.o
gcc -c qes.c -o qes.o

gcc -c ut.c -o ut.o
gcc -c qes_ut.c -o qes_ut.o
gcc qes_ut.o ut.o qes.o -lm -o qes_ut

./qes_ut

gcc main.o qes.o  -lm -o qes_exe

