#include "binder_demo.h"

#include <functional>
#include <iostream>

#include "person.h"

namespace binder_demo {

static double f(double x) {
  return x * 2;
}

static inline void EXPERIMENT_SEPARATOR() {
  std::cout << "===============================================================" 
	    << std::endl << std::endl;
}

void listing1() {
  std::cout << "binder_demo::listing1" << std::endl;

  auto b1 = std::bind(f, std::placeholders::_1);
  double res1 =  b1(1);
  std::cout << "b1(1)= " << res1 << std::endl;
  EXPERIMENT_SEPARATOR();

  auto b2 = std::bind(f, 10.0);
  double res2 = b2();
  std::cout << "b2()= " << res2 << std::endl;
  EXPERIMENT_SEPARATOR();
  
  Person p1("A", "BB");
  std::cout << "Person: " << p1 << std::endl;
  auto b3 = std::bind(&Person::save, &p1);
  b3();
  EXPERIMENT_SEPARATOR();
}

} // namespace binder_demo

