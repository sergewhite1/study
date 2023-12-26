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
  /* Test Graph
   * A -> B -> C -> D -> E
   * File Targets (not Phony): A, B, C, E
   * Phony Target: E
  */

  Target tA(false); tA.SetName("A");
  Target tB(false); tB.SetName("B");
  Target tC(false); tC.SetName("C");
  Target tD(true);  tD.SetName("D");
  Target tE(false); tE.SetName("E");

  tA.AddPrerequisite(&tB);
  tB.AddPrerequisite(&tC);
  tC.AddPrerequisite(&tD);
  tD.AddPrerequisite(&tE);

  tA.SetNeedProduceFile(true);
  tB.SetNeedProduceFile(true);
  tC.SetNeedProduceFile(true);
  tE.Touch();

  std::cout << tA.GraphToStr() << std::endl;

  tA.Process();

  std::cout << "Process again..." << std::endl;

  tA.Process();

  TimeService::Release();

  return 0;
}
