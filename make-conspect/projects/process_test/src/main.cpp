#include <cstring>
#include <iomanip>
#include <iostream>
#include <set>
#include <stdexcept>
#include <sstream>
#include <vector>

#include "interface/target.h"
#include "interface/time_service.h"

int main(int argc, char* argv[])
{
  std::cout << "Hello!!!" << std::endl;

  std::cout << "argc=" << argc << std::endl;
  for (int i = 0; i < argc; i++)
  {
    std::cout << "argv[" << i << "]=" << argv[i] << std::endl;
  }

  Target tA(false); tA.set_name("A");
  Target tB(false); tB.set_name("B");
  Target tC(false); tC.set_name("C");
  Target tD(true); tD.set_name("D");
  Target tE(false); tE.set_name("E");

  tA.add_prerequisite(&tB);
  tB.add_prerequisite(&tC);
  tC.add_prerequisite(&tD);
  tD.add_prerequisite(&tE);

  std::cout << tA.graph_to_str() << std::endl;

  tA.process();

  std::cout << "Process again..." << std::endl;

  tA.process();

  return 0;
}
