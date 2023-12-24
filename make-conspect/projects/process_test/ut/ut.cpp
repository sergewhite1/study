#include <cstring>
#include <iomanip>
#include <iostream>

#include "interface/null_stream.h"
#include "interface/target.h"
#include "interface/time_service.h"

typedef int (*test_proc_t)(std::string& name);

static Target CreatePhTarget(const char* name)
{
  Target ret(false, nullptr);
  ret.SetName(name);
  return ret;
}

static Target CreateNPhTarget(const char* name)
{
  Target ret(true, nullptr);
  ret.SetName(name);
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

int nph_npf_nnf_from_nph_ut(std::string& name)
{
  // case 00
  name =  __FUNCTION__;

  // RunCommands Flags
  bool tA_RC = false;
  bool tB_RC = false;

  // Callbacks
  auto tA_RC_CB = [&tA_RC] () { tA_RC = true; };
  auto tB_RC_CB = [&tB_RC] () { tB_RC = true; };

  Target tA = CreateNPhTarget("A");
  tA.SetRunCommandsCallBack(tA_RC_CB);

  Target tB = CreateNPhTarget("B");
  tB.SetRunCommandsCallBack(tB_RC_CB);

  tA.AddPrerequisite(&tB);

  tA.Process();

  if (tB_RC == false)
  {
    return 1;
  }

  if (tB.Exists())
  {
    return 1;
  }

  if (tB.Ttime() != Target::INVALID_TIME)
  {
    return 1;
  }

  if (tA_RC == false)
  {
    return 1;
  }

  // process again

  tA_RC = false;
  tB_RC = false;

  tA.Process();

  if (tB_RC == false)
  {
    return 1;
  }

  if (tA_RC == false)
  {
    return 1;
  }

  return 0;
}

int process_1_ut(std::string& name)
{
  name = __FUNCTION__;

  TimeService* ts = TimeService::GetInstance();
  ts->SetTime(0);

  Target tA = CreatePhTarget("A");
  Target tB = CreatePhTarget("B");

  tA.AddPrerequisite(&tB);

  tB.Touch();
  tA.Process();
  //std::cout << "tB.Exists()=" << tB.Exists() << std::endl;
  //std::cout << "tB.Ttime()="  << tB.Ttime()  << std::endl;
  //std::cout << "tA.Exists()=" << tA.Exists() << std::endl;

  //tA.Process();
  return 0;
}

/* Take a look at sumple graph A -> B
 * prod. file - produce file as result of RunCommands
 * n.    file - need file in RunCommands
 *-------------------------------------|----------|------------------------|
 *    | Target A                       | Target B |                        |
 *    |--------------------------------|----------|------------------------|
 * No.|is_phony | prod. file | n. file | is_phony | comment (ut name)      |
 * ---|---------|------------|---------|----------|------------------------|
 * 00 |   false |      false |   false |    false | nph_npf_nnf_from_nph   |
 * 01 |   false |      false |   false |     true | nph_npf_nnf_from_ph    |
 * 02 |   false |      false |    true |    false | nph_npf_nf_from_nph    |
 * 03 |   false |      false |    true |     true | nph_npf_nf_from_ph     |
 * 04 |   false |       true |   false |    false | nph_pf_nnf_from_nph    |
 * 05 |   false |       true |   false |     true | nph_pf_nnf_from_ph     |
 * 06 |   false |       true |    true |    false | nph_pf_nf_from_nph     |
 * 07 |   false |       true |    true |     true | already tested in 03   |
 * 08 |    true |      false |   false |    false | ph_npf_nnf_form_nph    |
 * 09 |    true |      false |   false |     true | ph_npf_nnf_from_ph     |
 * 10 |    true |      false |    true |    false | ph_npf_nf_from_ph      |
 * 11 |    true |      false |    true |     true | already tested in 03   |
 * 12 |    true |       true |   false |    false | ph_pf_nnf_from_nph     |
 * 13 |    true |       true |   false |     true | ph_pf_nnf_from_ph      |
 * 14 |    true |       true |    true |    false | ph_pf_nf_from_nph      |
 * 15 |    true |       true |    true |     true | already tested in 03   |
 * ---|---------|------------|---------|----------|------------------------|
*/

test_proc_t TESTS[] = {
  two_diff_targets_ut,
  two_same_targets_ut,
  graph_to_str_simple_ut,
  graph_to_str_ut,
  time_service_ut,
  nph_npf_nnf_from_nph_ut, // case 00
  process_1_ut,
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
      std::cout << "[" << i + 1 << "/" << TEST_COUNT << "] "
                << std::setw(W) << std::left
                << name << " PASSED" << std::endl;
      passed++;
    }
    else
    {
      std::cout << "[" << i + 1 << "/" << TEST_COUNT << "] "
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
