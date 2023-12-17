#include <cstring>
#include <iomanip>
#include <iostream>

#include "interface/target.h"
#include "interface/time_service.h"

typedef int (*test_proc_t)(std::string& name);

int two_diff_targets_ut(std::string& name)
{
  name = __FUNCTION__;

  Target tA(false); tA.set_name("A");
  Target tB(false); tB.set_name("B");

  return 0;
}

int two_same_targets_ut(std::string& name)
{
  name = __FUNCTION__;
  int ret = 1;

  try
  {
    Target tA(false); tA.set_name("A");
    Target tB(false); tB.set_name("A");
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

  Target tA(false); tA.set_name("A");
  Target tB(false); tB.set_name("B");

  tA.add_prerequisite(&tB);

  std::stringstream ss;
  ss << "A -> B" << std::endl;

  std::string expected = ss.str();
  std::string actual = tA.graph_to_str();

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

  Target tA(false); tA.set_name("A");
  Target tB(false); tB.set_name("B");
  Target tC(false); tC.set_name("C");
  Target tD(false); tD.set_name("D");
  Target tF(false); tF.set_name("F");
  Target tX(false); tX.set_name("X");
  Target tY(false); tY.set_name("Y");
  Target tG(false); tG.set_name("G");

  tA.add_prerequisite(&tB);
  tB.add_prerequisite(&tC);
  tC.add_prerequisite(&tD);
  tB.add_prerequisite(&tF);
  tF.add_prerequisite(&tX);
  tF.add_prerequisite(&tY);
  tB.add_prerequisite(&tG);

  std::stringstream ss;
  ss << "C -> D" << std::endl;
  ss << "B -> C" << std::endl;
  ss << "F -> X" << std::endl;
  ss << "F -> Y" << std::endl;
  ss << "B -> F" << std::endl;
  ss << "B -> G" << std::endl;
  ss << "A -> B" << std::endl;

  std::string expected = ss.str();
  std::string actual = tA.graph_to_str();

  if (actual == expected)
  {
    ret = 0;
  }

  return ret;
}

int time_service_ut(std::string& name)
{
  name = __FUNCTION__;

  TimeService::SetTime(100);
  int t = TimeService::GetCurrentTime();

  if (t != 100)
  {
    return 1;
  }

  t = TimeService::UpdateTime();

  if (t != 101)
  {
    return 1;
  }

  int ret = 1;

  try
  {
    TimeService::SetTime(99);
  }
  catch(const TimeServiceException& e)
  {
    if ((e.currentTime() == 101) && (e.newTime() == 99))
    {
      ret = 0;
    }
  }

  return ret;
}

test_proc_t TESTS[] = {
  two_diff_targets_ut,
  two_same_targets_ut,
  graph_to_str_simple_ut,
  graph_to_str_ut,
  time_service_ut
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
                << name << ": FAILED" << std::endl;
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

  return ret;
}
