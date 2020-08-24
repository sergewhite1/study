#include <iostream>
#include <memory>

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

class A {
public:
  int f() {
    std::cout << "A::f()" << std::endl; 
    return 1;
  }

  int f() const {
    std::cout << "A::f() const" << std::endl; 
    return 2;
  }

  int f() volatile {
    std::cout << "A::f() volatile" << std::endl; 
    return 3;
  
  }
  int f() const volatile {
    std::cout << "A::f() const volatile" << std::endl; 
    return 4;
  }

};

int main() {
  std::cout << "volatile demo" << std::endl;
  std::cout << "1. function demo" << std::endl;
  int x1 = 123456;

  f(&x1);

  f(const_cast<const int*>(&x1));

  f(const_cast<volatile int*>(&x1));

  f(const_cast<const volatile int*>(&x1));

  std::cout << "======================================" << std::endl;

  std::cout << "2. member-function demo" << std::endl;
  auto a_uptr = std::make_unique<A>();

  a_uptr->f();

  const_cast<const A*>(a_uptr.get())->f();

  const_cast<volatile A*>(a_uptr.get())->f();

  const_cast<const volatile A*>(a_uptr.get())->f();

  return 0;
}
