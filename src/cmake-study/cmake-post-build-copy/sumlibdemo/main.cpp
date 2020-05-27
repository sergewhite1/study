#include <iostream>

#include <dlfcn.h>
#include <unistd.h>

//#include "sumlib.h"

//namespace sumlib {
//  int (*add_func)(int, int);
//}

typedef int (*add_func_t)(int, int);

int main() {
  std::cout << "sumlibdemo" << std::endl;

  static const size_t MAX_PATH = 1024;
  char CWD[MAX_PATH];
  getcwd(CWD, MAX_PATH);
  std::cout << "current working direcory: " << CWD << std::endl;

  static const char* FILE_NAME = "./libsumlib.so";

  void *handle = nullptr;
  int ret = 0;

  do {
    handle = dlopen(FILE_NAME, RTLD_LAZY);
    if (handle == nullptr) {
      std::cerr << "Error of loading shared object: " << FILE_NAME << std::endl;
      std::cerr << dlerror() << std::endl;
      ret = 1;
      break;
    }

    int a = 10;
    int b = 2;
    std::cout << "a= " << a << "; b= " << b << std::endl;

//    int c = sumlib::add(a, b);

    add_func_t add = reinterpret_cast<add_func_t>(dlsym(handle, "add"));
    if (add == nullptr) {
      std::cerr << "dlsym error." << std::endl;
      std::cerr << dlerror() << std::endl;
      ret = 1;
      break;
    }

    int c = add(a, b);
    std::cout << "c=" << c << std::endl;
  } while (false);

  if (handle) {
    dlclose(handle);
  }
  
  return ret;
}
