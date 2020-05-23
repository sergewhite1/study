// See: https://www.youtube.com/watch?v=vVA46EvbL4E
// At the end of the lecture.

#ifndef THECHNOSPHERA_TIMER_H_
#define THECHNOSPHERA_TIMER_H

#include <chrono>
#include <iostream>

namespace technosphera {

class Timer {
  using clock_t = std::chrono::high_resolution_clock;
  using microseconds = std::chrono::microseconds;

public:
  Timer(): start_(clock_t::now()) {}

  ~Timer() {
    const auto finish = clock_t::now();
    const auto us = std::chrono::duration_cast<microseconds>(finish - start_).count();
    
    std::cout << "us: " << us << std::endl;
  }

private:
  const clock_t::time_point start_;
};

} // namespace technosphera

#endif
