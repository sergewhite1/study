/* Multithreading Practice.
   Anthony Williams. C++ Concurency in Action. Chapter 5.2.
   std::atomic_flag demo for spinlock_mutex.
*/

#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

class spinlock_mutex{
public:

  void lock() {
    while(flag_.test_and_set(std::memory_order_acquire));
  }

  void unlock() {
    flag_.clear(std::memory_order_release);
  }

private:
  std::atomic_flag flag_ = ATOMIC_FLAG_INIT;

};

static spinlock_mutex m;

static void thread_proc() {
  std::cout << "New  Thread ID= " << std::this_thread::get_id() << std::endl;
  std::lock_guard<spinlock_mutex> lg(m);
  std::cout << "New Thread. Mutex is locked by new thread" << std::endl;
  for (int n = 10; n >=0 ; --n) {
    std::cout << n << ' ';
    std::cout.flush();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << std::endl;
  std::cout << "New Thread. End Of Thread Proc" << std::endl;
}


int main() {
  std::cout << "memory-model-atomic-operations" << std::endl;
  std::cout << "Main Thread ID= " << std::this_thread::get_id() << std::endl;


  //std::thread t(thread_proc);
  //t.join();

  auto f = std::async(std::launch::async, thread_proc);

  std::this_thread::sleep_for(std::chrono::seconds(2));

  std::cout << "Main Thread. Wait for mutex." << std::endl;

  std::lock_guard<spinlock_mutex> lg(m);

  std::cout << "Main Thread. Mutex is locked by main thread." << std::endl;

  f.get();

  return 0;
}
