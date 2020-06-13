#include <iostream>

static int f(int* ptr_x) {
  std::cout << "f(int* ptr_x). ptr_x=" << ptr_x <<  " *ptr_x=" << *ptr_x << std::endl;
  return *ptr_x + 1;
}

static int f(const int*  ptr_x) {
  std::cout << "f(const int* ptr_x). ptr_x=" << ptr_x << " *ptr_x=" << *ptr_x << std::endl;
  return *ptr_x + 2;
}

static int f(volatile int* ptr_x) {
  std::cout << "f(volatile int* ptr_x). ptr_x=" << ptr_x << " *ptr_x=" << *ptr_x << std::endl;
  return *ptr_x + 3;
}

static int f(const volatile int* ptr_x) {
  std::cout << "f(const volatile int* ptr_x). ptr_x=" << ptr_x << " *ptr_x=" << *ptr_x << std::endl;
  return *ptr_x + 4;
}

int main() {
  std::cout << "volatile demo" << std::endl;
  int x1 = 0;
  int y1 = f(&x1);
  std::cout << "y1=" << y1 << std::endl;

  int x2 = 0;
  int y2 = f(const_cast<const int*>(&x2));
  std::cout << "y2= " << y2 << std::endl;

  int data3 = 100;
  volatile int * x3 = &data3;
  int y3 = f(x3);
  std::cout << "y3= " << y3 << std::endl;

  int data4 = 200;
  const volatile int * x4 = &data4;
  int y4 = f(x4);
  std::cout << "y4= " << y4 << std::endl;

  return 0;
}
