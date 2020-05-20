#include <cstring>
#include <iostream>
#include <thread>

struct A {
  // x and y place in 2 memory cells
  int x = 0;
  int y = 0;

  // bf1 and bf2 place in same memory cell
  // it is not thread safe !!!!!
  int bf1 : 4;
  int bf2 : 4;

  int dummy;

  // bf3 and bf5 places in different memory cells
  // it is thread safe !!!
  int bf3 : 4;
  int     : 0;
  int bf5 : 4;
};

static A aObj;

static void thread_proc_1() {
  std::cout << "func: thread_proc_1. thread id: " << std::this_thread::get_id()
            << std::endl;
  for (size_t i = 0; i < 2000000000; ++i) {
    ++aObj.x;
    aObj.bf1 += 1;
    aObj.bf3 += 1;
    if (i > 1999999990) {
      std::cout << "!!! Obj {bf1= " << aObj.bf1 <<"; bf3=" << aObj.bf3 << "}!!!";
    }
  }
  std::cout << std::endl;
}

static void thread_proc_2() {
  std::cout << "func: thread_proc_2. thread id: " << std::this_thread::get_id()
            << std::endl;
  for (size_t i = 0; i < 1000000000; ++i) {
    ++aObj.y;
    aObj.bf2 += 1;
    aObj.bf5 += 1;
    if (i > 999999990) {
      std::cout << "@@@ Obj {bf2= " << aObj.bf2 << "; bf5=" << aObj.bf5 << "}@@@";
    }
  }
  std::cout << std::endl;
}

//#define DEBUG_RESEARCH

int main() {
  std::cout << "memory-model-basic" << std::endl;
  std::cout << "sizeof(A)=" << sizeof(A) << std::endl;

#ifdef DEBUG_RESEARCH

  A aObj2;
  memset(&aObj2, 0, sizeof(aObj2));

  aObj2.x = 0xA2A1A0;
  aObj2.y = 0xB2B1B0;

  aObj2.bf1 = -1; // 0xFF
  aObj2.bf2 = -8; // 1000
  // byte: 0x8F

  aObj2.dummy = 0x01020304;

  aObj2.bf3 = -1;
  aObj2.bf5 = -8;

  std::cout << "aObj2: {x=" << aObj2.x << "; y=" << aObj2.y
            << "; bf1=" << aObj2.bf1 << "; bf2=" << aObj2.bf2
            << "; dummy= " << aObj2.dummy
            << "; bf3= " << aObj2.bf3 << "; bf5=" << aObj2.bf5
            <<  "}" << std::endl;

  return 0;

#endif

  std::cout << "main thread id: " << std::this_thread::get_id() << std::endl;

//  aObj.bf1 = 0;
//  aObj.bf2 = 0;
//  aObj.bf3 = 0;
//  aObj.bf5 = 0;
  std::cout << "aObj.bf1= " << aObj.bf1 << std::endl;
  std::cout << "aObj.bf2= " << aObj.bf2 << std::endl;
  std::cout << "aObj.bf3= " << aObj.bf3 << std::endl;
  std::cout << "aObj.bf5= " << aObj.bf5 << std::endl;

  std::thread t1(thread_proc_1);
  std::thread t2(thread_proc_2);

  std::this_thread::sleep_for(std::chrono::milliseconds(50));
  std::cout << "Inside work ";
  std::cout << "aObj.x=  "  << aObj.x   << " aObj.y=   " << aObj.y << " " 
            << "aObj.bf1= " << aObj.bf1 << " aObj.bf2= " << aObj.bf2
            << std::endl;
 
  t1.join();
  t2.join();

  std::cout << "Thread finished." << std::endl;
  std::cout << "aObj.x=  "  << aObj.x   << " aObj.y=   " << aObj.y   << " "
            << "aObj.bf1= " << aObj.bf1 << " aObj.bf2= " << aObj.bf2 << " "
            << "aObj.bf3= " << aObj.bf3 << " aObj.bf5= " << aObj.bf5 
            << std::endl;

  //aObj.bf1 = -10;
  //aObj.bf2 = -1;
  
  //std::cout << "aObj.bf1= " << aObj.bf1 << " aObj.bf2= " << aObj.bf2 << std::endl;

  return 0;
}
