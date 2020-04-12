#include <iostream>

static void proc1();

int main() {
  std::cout << "STACK RESEARCH" << std::endl;
  int a = 0;
  std::cout << "&a= " << &a << std::endl;

  proc1();

  return 0;
}

static void proc1() {
  int b = 1;
  //std::cout << "Proc1" << std::endl;
  std::cout << "&b= " << &b << std::endl;
}
