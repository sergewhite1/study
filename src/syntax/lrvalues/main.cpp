#include <iostream>

#include "a.h"
#include "functions.h"

int main() {
  std::cout <<"sizeof(A) = " << sizeof(A) << " bytes" << std::endl;

  rvo_test();
  nrvo_test();
  return_object_move_ctor_demo(3);
  swap_objects();
  vector_push_back();
  string_literal_is_lvalue_ref();

  // int& x = 47;        // compile error!
  // const int& x = 47;  // OK
  // int&& x = 47;       // OK
  // std::cout << "x = " << x << std::endl;

  // A&& aObj {"AAA"};   // OK
  // std::cout << "aObj = " << aObj << std::endl;
  // A aObj2(aObj));     // call copy ctor !
  // A aObj2(std::move(aObj));
  // std::cout << "aObj2 = " << aObj2 << std::endl;
}
