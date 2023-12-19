#include <cstring>
#include <iomanip>
#include <iostream>

#include "interface/null_stream.h"
#include "interface/target.h"
#include "interface/time_service.h"

typedef int (*test_proc_t)(std::string& name);

static Target CreateTarget(const char* name)
{
  Target ret(false, nullptr);
  ret.SetName(name);
  return ret;
}

int two_diff_targets_ut(std::string& name)
{
  name = __FUNCTION__;

  Target tA = CreateTarget("A");
  Target tB = CreateTarget("B");

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
    if (std::strcmp(e.name(), "A") == 0)
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

  Target tA = CreateTarget("A");
  Target tB = CreateTarget("B");

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

  Target tA = CreateTarget("A");
  Target tB = CreateTarget("B");
  Target tC = CreateTarget("C");
  Target tD = CreateTarget("D");
  Target tF = CreateTarget("F");
  Target tX = CreateTarget("X");
  Target tY = CreateTarget("Y");
  Target tG = CreateTarget("G");

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

int process_1_ut(std::string& name)
{
  name = __FUNCTION__;

  TimeService* ts = TimeService::GetInstance();
  ts->SetTime(0);

  Target tA = CreateTarget("A");
  Target tB = CreateTarget("B");

  tA.AddPrerequisite(&tB);

  tA.Process();
  tB.Touch();
  tA.Process();

  return 0;
}

test_proc_t TESTS[] = {
  two_diff_targets_ut,
  two_same_targets_ut,
  graph_to_str_simple_ut,
  graph_to_str_ut,
  time_service_ut,
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
