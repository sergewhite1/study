#include <cstring>
#include <iostream>

static void f() {
}

int main(int argc, char* argv[]) {
  std::cout << "Optimization demo." << std::endl;
  std::cout << "Run: ./optimization false" << std::endl;
  std::cout << "Default value: true" << std::endl;

  bool a = true;

  if (argc >= 2) {
    if (strcmp(argv[1], "true") == 0) {
      a = true;
    } else if (strcmp(argv[1], "false") == 0) {
      a = false;
    } else {
      std::cerr << "Unexpected flag: " << argv[1] << ". Expected values:{false, true}." << std::endl;
      return 1;
    }
  }

  const int N = 10000;
  
  std::cout << "FLAG= " << a << " N= " << N << std::endl;

  for (size_t i = 0; i < N; ++i) {
    if(a) {
      f();
    } else {
      f();
    }
  }
  
  return 0;
}
