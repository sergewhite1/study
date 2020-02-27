#include <iostream>

#include "wht_string.h"

int main() {
  std::cout << "Short String Optimization Demo" << std::endl;

  wht::string s("BLA BLA BLA...");
  std::cout << "s= " << s << std::endl;

	std::cout << "sizeof(size_t)=" << sizeof(size_t) << std::endl;

  return 0;
}
