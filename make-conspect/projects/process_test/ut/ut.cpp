#include <cstring>
#include <iomanip>
#include <iostream>

#include "interface/null_stream.h"
#include "interface/target.h"
#include "interface/time_service.h"

typedef int (*test_proc_t)(std::string& name);

static Target CreatePhTarget(const char* name)
{
  Target ret(true, nullptr);
  ret.SetName(name);
  return ret;
}

static Target CreateNPhTarget(const char* name, bool needProduceFile)
{
  Target ret(false, nullptr);
  ret.SetName(name);
  ret.SetNeedProduceFile(needProduceFile);
  return ret;
}

int two_diff_targets_ut(std::string& name)
{
  name = __FUNCTION__;

  Target tA = CreatePhTarget("A");
  Target tB = CreatePhTarget("B");

  return 0;
}

int two_same_targets_ut(std::string& name)
{
  name = __FUNCTION__;
  int ret = 1;

  try
  {
    Target tA(false); tA.SetName("A");
    Target tB(false); tB.SetName("A");
  }
  catch(const BadTargetName& e)
  {
    if (std::strcmp(e.TargetName().c_str(), "A") == 0)
    {
      ret = 0;
    }
  }

  return ret;
}

int graph_to_str_simple_ut(std::string& name)
{
  name = __FUNCTION__;

  int ret = 1;

  Target tA = CreatePhTarget("A");
  Target tB = CreatePhTarget("B");

  tA.AddPrerequisite(&tB);

  std::stringstream ss;
  ss << "A -> B" << std::endl;

  std::string expected = ss.str();
  std::string actual = tA.GraphToStr();

  if (actual == expected)
  {
    ret = 0;
  }

  return ret;
}

int graph_to_str_ut(std::string& name)
{
  name = __FUNCTION__;

  int ret = 1;

  Target tA = CreatePhTarget("A");
  Target tB = CreatePhTarget("B");
  Target tC = CreatePhTarget("C");
  Target tD = CreatePhTarget("D");
  Target tF = CreatePhTarget("F");
  Target tX = CreatePhTarget("X");
  Target tY = CreatePhTarget("Y");
  Target tG = CreatePhTarget("G");

  tA.AddPrerequisite(&tB);
  tB.AddPrerequisite(&tC);
  tC.AddPrerequisite(&tD);
  tB.AddPrerequisite(&tF);
  tF.AddPrerequisite(&tX);
  tF.AddPrerequisite(&tY);
  tB.AddPrerequisite(&tG);

  std::stringstream ss;
  ss << "C -> D" << std::endl;
  ss << "B -> C" << std::endl;
  ss << "F -> X" << std::endl;
  ss << "F -> Y" << std::endl;
  ss << "B -> F" << std::endl;
  ss << "B -> G" << std::endl;
  ss << "A -> B" << std::endl;

  std::string expected = ss.str();
  std::string actual = tA.GraphToStr();

  if (actual == expected)
  {
    ret = 0;
  }

  return ret;
}

int time_service_ut(std::string& name)
{
  name = __FUNCTION__;

  TimeService *ts = TimeService::GetInstance();

  ts->SetTime(100);
  int t = ts->GetCurrentTime();

  if (t != 100)
  {
    return 1;
  }

  t = ts->UpdateTime();

  if (t != 101)
  {
    return 1;
  }

  return 0;
}

int nph_npf_from_nph_ut(std::string& name)
{
  // case 00

  name =  __FUNCTION__;

  // RunCommands Flags
  bool tA_RC = false;
  bool tB_RC = false;

  // Callbacks
  auto tA_RC_CB = [&tA_RC] () { tA_RC = true; };
  auto tB_RC_CB = [&tB_RC] () { tB_RC = true; };

  Target tA = CreateNPhTarget("A", false);
  tA.SetRunCommandsCallBack(tA_RC_CB);

  Target tB = CreateNPhTarget("B", false);
  tB.Touch();
  tB.SetRunCommandsCallBack(tB_RC_CB);

  tA.AddPrerequisite(&tB);

  tA.Process();

  if (!(tB_RC == false))
  {
    return 1;
  }

  if (!tB.Exists())
  {
    return 1;
  }

  if (!(tA.Exists() == false))
  {
    return 1;
  }

  if (!(tA_RC == true))
  {
    return 1;
  }

  // process again

  tA_RC = false;
  tB_RC = false;

  tA.Process();

  if (!(tB_RC == false))
  {
    return 1;
  }

  if (!tB.Exists())
  {
    return 1;
  }

  if (!(tA.Exists() == false))
  {
    return 1;
  }

  if (!(tA_RC == true))
  {
    return 1;
  }

  return 0;
}

int nph_npf_from_ph_ut(std::string& name)
{
  // case 01

  name = __FUNCTION__;

  Target tA = CreateNPhTarget("A", false);
  Target tB = CreatePhTarget("B");

  tA.AddPrerequisite(&tB);

  // RunCommands Flags
  bool tA_RC = false;
  bool tB_RC = false;

  // Callbacks
  auto tA_RC_CB = [&tA_RC] () { tA_RC = true; };
  auto tB_RC_CB = [&tB_RC] () { tB_RC = true; };

  tA.SetRunCommandsCallBack(tA_RC_CB);
  tB.SetRunCommandsCallBack(tB_RC_CB);

  tA.Process();

  if (!(tB_RC == true))
  {
    return 1;
  }

  if (!(tB.Exists() == false))
  {
    return 1;
  }

  if (!(tA_RC == true))
  {
    return 1;
  }

  if (!(tA.Exists() == false))
  {
    return 1;
  }

  // run process again

  tA_RC = false;
  tB_RC = false;

  tA.Process();

  if (!(tB_RC == true))
  {
    return 1;
  }

  if (!(tB.Exists() == false))
  {
    return 1;
  }

  if (!(tA_RC == true))
  {
    return 1;
  }

  if (!(tA.Exists() == false))
  {
    return 1;
  }

  return 0;
}

int nph_pf_from_nph_ut(std::string& name)
{
  // case 02

  name = __FUNCTION__;

  Target tA = CreateNPhTarget("A", true);
  Target tB = CreateNPhTarget("B", false);

  tA.AddPrerequisite(&tB);

  TimeService::GetInstance()->SetTime(0);

  tB.Touch();

  tA.Process();

  if(!(tB.Exists() == true))
  {
    return 1;
  }

  if (!(tB.Ttime() == 1))
  {
    return 1;
  }

  if (!(tA.Exists() == true))
  {
    return 1;
  }

  if (!(tA.Ttime() == 2))
  {
    return 1;
  }

  // process again

  tA.Process();

  if(!(tB.Exists() == true))
  {
    return 1;
  }

  if (!(tB.Ttime() == 1))
  {
    return 1;
  }

  if (!(tA.Exists() == true))
  {
    return 1;
  }

  if (!(tA.Ttime() == 2))
  {
    return 1;
  }

  tB.Touch();

  // process again

  tA.Process();

  if(!(tB.Exists() == true))
  {
    return 1;
  }

  if (!(tB.Ttime() == 3))
  {
    return 1;
  }

  if (!(tA.Exists() == true))
  {
    return 1;
  }

  if (!(tA.Ttime() == 4))
  {
    return 1;
  }

  return 0;
}


int nph_pf_from_ph_ut(std::string& name)
{
  // case 03

  name = __FUNCTION__;

  TimeService::GetInstance()->SetTime(0);

  Target tA = CreateNPhTarget("A", true);
  Target tB = CreatePhTarget("B");

  tA.AddPrerequisite(&tB);

  tA.Process();

  if (!(tB.Exists() == false))
  {
    return 1;
  }

  if (!(tA.Exists() == true))
  {
    return 1;
  }

  if (!(tA.Ttime() == 1))
  {
    return 1;
  }

  // process again

  tA.Process();

  if (!(tB.Exists() == false))
  {
    return 1;
  }

  if (!(tA.Exists() == true))
  {
    return 1;
  }

  if (!(tA.Ttime() == 2))
  {
    return 1;
  }

  return 0;
}


int ph_npf_from_nph_ut(std::string& name)
{
  // case 04

  name = __FUNCTION__;

  TimeService::GetInstance()->SetTime(0);

  Target tA = CreatePhTarget("A");
  Target tB = CreateNPhTarget("B", false);

  tA.AddPrerequisite(&tB);
  tB.Touch();

  // RunCommands Flags
  bool tA_RC = false;
  bool tB_RC = false;

  // Callbacks
  auto tA_RC_CB = [&tA_RC] () { tA_RC = true; };
  auto tB_RC_CB = [&tB_RC] () { tB_RC = true; };

  tA.SetRunCommandsCallBack(tA_RC_CB);
  tB.SetRunCommandsCallBack(tB_RC_CB);

  tA.Process();

  if (!(tB.Exists() == true))
  {
    return 1;
  }

  if (!(tB.Ttime() == 1))
  {
    return 1;
  }

  if (!(tB_RC == false))
  {
    return 1;
  }

  if (!(tA.Exists() == false))
  {
    return 1;
  }

  if (!(tA_RC == true))
  {
    return 1;
  }

  tA_RC = false;
  tB_RC = false;

  // process again

  tA.Process();

  if (!(tB.Exists() == true))
  {
    return 1;
  }

  if (!(tB.Ttime() == 1))
  {
    return 1;
  }

  if (!(tB_RC == false))
  {
    return 1;
  }

  if (!(tA.Exists() == false))
  {
    return 1;
  }

  if (!(tA_RC == true))
  {
    return 1;
  }

  return 0;
}

int ph_npf_from_ph_ut(std::string& name)
{
  // case 05

  name = __FUNCTION__;

  Target tA = CreatePhTarget("A");
  Target tB = CreatePhTarget("B");

  tA.AddPrerequisite(&tB);

  // RunCommands Flags
  bool tA_RC = false;
  bool tB_RC = false;

  // Callbacks
  auto tA_RC_CB = [&tA_RC] () { tA_RC = true; };
  auto tB_RC_CB = [&tB_RC] () { tB_RC = true; };

  tA.SetRunCommandsCallBack(tA_RC_CB);
  tB.SetRunCommandsCallBack(tB_RC_CB);

  tA.Process();

  if (!(tB.Exists() == false))
  {
    return 1;
  }

  if (!(tB_RC == true))
  {
    return 1;
  }

  if (!(tA.Exists() == false))
  {
    return 1;
  }

  if (!(tA_RC == true))
  {
    return 1;
  }

  tA_RC = false;
  tB_RC = false;

  // process again

  tA.Process();

  if (!(tB.Exists() == false))
  {
    return 1;
  }

  if (!(tB_RC == true))
  {
    return 1;
  }

  if (!(tA.Exists() == false))
  {
    return 1;
  }

  if (!(tA_RC == true))
  {
    return 1;
  }

  return 0;
}

int research_1_ut(std::string& name)
{
  name = __FUNCTION__;

  /* Test Graph
   * A -> B -> C -> D -> E
   * File Targets (not Phony): A, B, C, E
   * Phony Target: E
  */

  Target tA = CreateNPhTarget("A", true);
  Target tB = CreateNPhTarget("B", true);
  Target tC = CreateNPhTarget("C", true);
  Target tD = CreatePhTarget("D");
  Target tE = CreateNPhTarget("E", false);

  tA.AddPrerequisite(&tB);
  tB.AddPrerequisite(&tC);
  tC.AddPrerequisite(&tD);
  tD.AddPrerequisite(&tE);

  TimeService::GetInstance()->SetTime(0);

  tE.Touch();

  //std::cout << tA.GraphToStr() << std::endl;

  tA.Process();

  if (!tE.Exists())
  {
    return 1;
  }

  if (!(tE.Ttime() == 1))
  {
    return 1;
  }

  if (!(tD.Exists() == false))
  {
    return 1;
  }

  if (!(tC.Exists() == true))
  {
    return 1;
  }

  if (!(tC.Ttime() == 2))
  {
    return 1;
  }

  if (!(tB.Exists() == true))
  {
    return 1;
  }

  if (!(tB.Ttime() == 3))
  {
    return 1;
  }

  if (!(tA.Exists() == true))
  {
    return 1;
  }

  if (!(tA.Ttime() == 4))
  {
    return 1;
  }

  tA.Process();

  // process again

  tA.Process();

  return 0;
}

/* Take a look at sumple graph A -> B
 * prod. file - produce file as result of RunCommands
 * n.    file - need file in RunCommands
 *---------------------------|----------|------------------------|
 *    | Target A             | Target B |                        |
 *    |----------------------|----------|------------------------|
 * No.|is_phony | prod. file | is_phony | comment (ut name)      |
 * ---|---------|------------|----------|------------------------|
 * 00 |   false |      false |   false  | nph_npf_from_nph_ut    |
 * 01 |   false |      false |    true  | nph_npf_from_ph_ut     |
 * 02 |   false |       true |   false  | nph_pf_from_nph_ut     |
 * 03 |   false |       true |    true  | nph_pf_from_ph_ut      |
 * 04 |    true |      false |   false  | ph_npf_from_nph_ut     |
 * 05 |    true |      false |    true  | ph_npf_from_ph_ut      |
 * 06 |    true |       true |   false  | does not have sense    |
 * 07 |    true |       true |    true  | does not have sense    |
 * ---|---------|------------|----------|------------------------|
*/

test_proc_t TESTS[] = {
  two_diff_targets_ut,
  two_same_targets_ut,
  graph_to_str_simple_ut,
  graph_to_str_ut,
  time_service_ut,
  nph_npf_from_nph_ut, // case 00
  nph_npf_from_ph_ut,  // case 01
  nph_pf_from_nph_ut,  // case 02
  nph_pf_from_ph_ut,   // case 03
  ph_npf_from_nph_ut,  // case 04
  ph_npf_from_ph_ut,   // case 05
  research_1_ut
};

static constexpr int TEST_COUNT = sizeof(TESTS) / sizeof(TESTS[0]);

int main()
{
  constexpr int W = 30;

  int count  = 0;
  int passed = 0;
  int failed = 0;
  int ret    = 0;

  for (int i = 0; i < TEST_COUNT; i++)
  {
    int err_code = 0;
    std::string name;

    err_code = TESTS[i](name);

    if (err_code == 0)
    {
      std::cout << "[" << std::setw(2) << std::right << i + 1
                << "/" << std::setw(2) << TEST_COUNT << "] "
                << std::setw(W) << std::left
                << name << " PASSED" << std::endl;
      passed++;
    }
    else
    {
      std::cout << "[" << std::setw(2) << std::right << i + 1
                << "/" << std::setw(2) << TEST_COUNT << "] "
                << std::setw(W) << std::left
                << name << " FAILED" << std::endl;
      failed++;
      ret = 1;
    }

    count++;
  }

  std::cout << "Total: " << count << " Passed: " << passed << " Failed: " << failed << std::endl;

  if (ret == 0)
  {
    std::cout << "SUCCESS" << std::endl;
  }
  else
  {
    std::cout << "FAILED" << std::endl;
  }

  TimeService::Release();

  return ret;
}
