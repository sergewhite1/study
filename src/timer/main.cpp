#include <iostream>
#include <thread>

#include "technosphera/technosphera_timer.h"

int main() {
  std::cout << "timer demo" << std::endl;
  {
    volatile technosphera::Timer t;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}
