#include <stdio.h>
#include <stdlib.h>

int main() {
  printf("to see memory leak report run valgrind:\n");
  printf("valgrind ./valgrind-demo\n");
  int * p = (int*) malloc(1024);
  (void)p;
  return 0;
}
