#include <chrono>
#include <iostream>

bool f1()
{
  bool a = true;
  bool b = false;
  bool c = true;

  bool ret = a;
  ret &= b;
  ret &= c;

  return ret;
}

bool f2()
{
  bool a = true;
  bool b = false;
  bool c = true;

  bool ret = a && b && c;

  return ret;
}

using time_point = std::chrono::high_resolution_clock::time_point;

std::string time_point_to_str(const time_point& tp)
{
  std::time_t t = std::chrono::high_resolution_clock::to_time_t(tp);
  return std::ctime(&t);
}

int main() {
  std::cout << "Hello, World!" << std::endl;

  constexpr size_t N = 1'000'000'000;

  std::cout << "Testing f1..." << std::endl;

  auto t1 = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < N; ++i)
  {
    f1();
  }

  auto t2 = std::chrono::high_resolution_clock::now();

  auto dt = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "t1= " << time_point_to_str(t1);
  std::cout << "t2= " << time_point_to_str(t2);
  std::cout << "dt= " << dt << "ms" << std::endl;

  std::cout << "Testing f2..." << std::endl;

  t1 = std::chrono::high_resolution_clock::now();

  for (size_t i = 0; i < N; ++i)
  {
    f2();
  }

  t2 = std::chrono::high_resolution_clock::now();

  dt = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

  std::cout << "t1= " << time_point_to_str(t1);
  std::cout << "t2= " << time_point_to_str(t2);
  std::cout << "dt= " << dt << "ms" << std::endl;

  return 0;
}
