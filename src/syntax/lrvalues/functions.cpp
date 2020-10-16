#include "functions.h"

#include <iostream>
#include <vector>

#include "a.h"

static A create_a_rvo() {
  std::cout << "A create_a_rvo()" << std::endl;
  return A("Hello from create_a_rvo.");
}

void rvo_test() {
  std::cout << "rvo_test begin==================================" << std::endl;
  {
    A a_obj = create_a_rvo();
    std::cout << "a_obj = " << a_obj << std::endl;
  }
  std::cout << "rvo_test end====================================" << std::endl;
}

static A create_a_nrvo() {
  std::cout << "A create_a_nrvo()" << std::endl;
  A ret;
  ret.setData("Hello from create_a_nrvo");

  return ret;

  // explict turn off nrvo and use move ctor
  //return std::move(ret);
}

void nrvo_test() {
  std::cout << "nrvo_test begin=================================" << std::endl;
  {
    A a_obj = create_a_nrvo();
    std::cout << "a_obj = " << a_obj << std::endl;
  }
  std::cout << "nrvo_test end===================================" << std::endl;
}

static A create_a_move_ctor_demo(int factor) {
  A a_obj_1("Hello from create_a_move_ctor_demo factor < 10");
  A a_obj_2("Hello from create_a_move_ctor_demo factor >= 10");

  if (factor < 10) {
    return a_obj_1;
  } 

  return a_obj_2;

/* In this case RVO works
  if (factor < 10) {
    return A("Hello from create_a_move_ctor_demo factor < 10");
  }

  return A("Hello from create_a_move_ctor_demo factor >= 10");
*/
}


void return_object_move_ctor_demo(int factor) {
  std::cout << "return_object_move_ctor_demo factor = " << factor << " begin==================" << std::endl;
  {
    A a_obj = create_a_move_ctor_demo(factor);
    std::cout << "a_obj = " << a_obj << std::endl;
  }
  std::cout << "return_object_move_ctor_demo end===============================" << std::endl;
}

void swap_objects() {
  std::cout << "swap_objects begin==============================" << std::endl;
  {
    A a_obj_1("a_obj_1");
    A a_obj_2("a_obj_2");
    
    A temp = std::move(a_obj_1);
    a_obj_1 = std::move(a_obj_2);
    a_obj_2 = std::move(temp);
 
    std::cout << "a_obj_1 = " << a_obj_1 << std::endl;
    std::cout << "a_obj_2 = " << a_obj_2 << std::endl;
    std::cout << "temp    = " << temp << std::endl;
  }
  std::cout << "swap_objects end================================" << std::endl;
}

void vector_push_back() {
  std::cout << "vector_push_back begin==========================" << std::endl; 
  {
    std::vector<A> v;
    v.reserve(2);
    A aObj1("aObj1");
    v.push_back(aObj1);

    A aObj2("aObj2");
    v.push_back(std::move(aObj2));

    std::cout << "aObj1 = " << aObj1 << std::endl;
    std::cout << "aObj2 = " << aObj2 << std::endl;

    size_t index = 0;
    for (const auto & elem : v) {
      std::cout << "v[" << index++ << "] = " << elem << std::endl;
    }
  }
  std::cout << "vector_push_back end============================" << std::endl;
}

void string_literal_is_lvalue_ref() {
  std::cout << "string_literal_is_lvalue_ref begin=============================" << std::endl;
  {
    auto p = &"Hello, World!";
    std::cout << "p = " << p << std::endl;
  }
  std::cout << "string_literal_is_lvalue_ref end===============================" << std::endl;
}
