#include <stdio.h>

int main() {
  printf("memory maps demo.\n");
  printf("on linux you can see memory maps in virtual file: /proc/<PID>/maps\n");
  printf("press any key to exit...");
  getchar();
  return 0;
}
