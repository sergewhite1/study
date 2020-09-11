#include <atomic>
#include <iostream>

static std::atomic<bool> g_flag(true);

int main() {
  std::cout << "is_lock_free = " << g_flag.is_lock_free() << std::endl;
  bool b = g_flag.load();
  std::cout << "b = " << b << std::endl;
  return 0;
}
