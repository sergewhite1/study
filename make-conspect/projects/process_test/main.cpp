#include <cstring>
#include <iostream>
#include <set>
#include <stdexcept>
#include <sstream>
#include <vector>

class BadTargetName : public std::runtime_error
{
  public:
    BadTargetName(const char* bad_target_name)
    : std::runtime_error(bad_target_name)
    {
      name_.append(bad_target_name);
      str_ = "Bad Target Name: " + name_;
    }

    // std::exception interface
    virtual const char* what() const noexcept
    {
      return str_.c_str();
    }

    const char* name() const noexcept
    {
      return name_.c_str();
    }

  private:
    std::string str_;
    std::string name_;
};

class TargetStopProcessing : public std::runtime_error
{
  public:
    TargetStopProcessing(const std::string& name)
    : std::runtime_error("TargetStopProcessing")
    , name_(name)
    {
      str_ = "TargetStopProcessing. Name: " + name;
    }

    // std::exception interface
    virtual const char* what() const noexcept
    {
      return str_.c_str();
    }

    std::string name() const { return name_; }

  private:
    std::string str_;
    std::string name_;
};

class TimeServiceException : public std::runtime_error
{
  public:
    TimeServiceException(int currentTime, int newTime)
    : std::runtime_error("TimeServiceException")
      ,currentTime_(currentTime)
      ,newTime_(newTime)
    {
      std::stringstream ss;

      ss << "TimeServiceException. currentTime MUST be < newTime,"
         << " currentTime=" << currentTime_
         << ", newTime=" << newTime_;

      str_ = ss.str();
    }

    // std::exception interface
    virtual const char* what() const noexcept
    {
      return str_.c_str();
    }

    int currentTime() const { return currentTime_; }
    int newTime() const { return newTime_; };

  private:
    std::string str_;
    int currentTime_ = 0;
    int newTime_     = 0;
};

class TimeService
{
  public:
    static int  GetCurrentTime() { return TimeService::CURRENT_TIME; }
    static int UpdateTime() { return ++TimeService::CURRENT_TIME; }
    static void SetTime(int value);

  private:
    static int CURRENT_TIME;
};

int TimeService::CURRENT_TIME = 0;

void TimeService::SetTime(int value)
{
  if (!(TimeService::GetCurrentTime() < value))
  {
    throw TimeServiceException(TimeService::GetCurrentTime(), value);
  }

  TimeService::CURRENT_TIME = value;
}

class Target
{
  public:
    Target(bool is_phony);
    ~Target();

    std::string name() const { return name_; }
    void set_name(const std::string name);

    void add_prerequisite(Target* target);
    void process();

    std::string graph_to_str() const;
    bool is_phony() const { return is_phony_; }

    bool exists() const { return exists_; }
    int ttime() const { return ttime_; }
    bool run_commands()
    {
      std::cout << "Make target: " << name() << std::endl;
      return true;
    }

  private:
    static std::set<std::string> NAMES;

    std::string name_;
    std::vector<Target*> prerequisites_;
    bool is_phony_ = false;
    bool exists_   = false;
    int ttime_     = 0;

    void graph_to_str(std::stringstream& ss) const;
};

std::set<std::string> Target::NAMES;

Target::Target(bool is_phony)
  : is_phony_(is_phony)
{}

Target::~Target()
{
  if (!name_.empty())
  {
    Target::NAMES.erase(name_);
  }
}

void Target::set_name(const std::string name)
{
  if (Target::NAMES.find(name) != Target::NAMES.end())
  {
    throw BadTargetName(name.c_str());
  }

  NAMES.insert(name);
  name_ = name;
}

void Target::add_prerequisite(Target* target)
{
  prerequisites_.push_back(target);
}

void Target::process()
{
  bool need_build = true;

  if (!is_phony() && exists())
  {
    need_build = false;
  }

  for (auto* prereq : prerequisites_)
  {
    prereq->process();

    if (prereq->is_phony())
    {
      need_build = true;
    }
    else if (!is_phony())
    {
      // Here we are
      if (!(ttime() > prereq->ttime()))
      {
        need_build = true;
      }
    }
  }

  if (need_build)
  {
    if (run_commands())
    {
      if (!is_phony())
      {
        exists_ = true;
        ttime_  = TimeService::UpdateTime();
      }
    }
    else
    {
      std::cout << "Error in target: " << name() << std::endl;
      std::cout << "Stop processing";
      throw TargetStopProcessing(name());
    }
  }
  else
  {
    std::cout << "Target " << name() << " is up to date." << std::endl;
  }
}

/* For Graph:
 * A -> B -> C -> D
 *      |\
 *      | \
 *      G  F -> X
 *         |
 *         Y
 * Output will be:
 * A -> B
 * B -> C
 * C -> D
 * B -> F
 * F -> X
 * F -> Y
 * B -> G
 *
 * See in Unit Test
*/

std::string Target::graph_to_str() const
{
  std::stringstream ss;
  graph_to_str(ss);
  return ss.str();
}

void Target::graph_to_str(std::stringstream& ss) const
{
  for (const auto * prereq : prerequisites_)
  {
    prereq->graph_to_str(ss);
    ss << name() << " -> " << prereq->name() << std::endl;
  }
}

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

static int run_ut()
{
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
      std::cout << "[" << i + 1 << "/" << TEST_COUNT << "] " << name << ": PASSED" << std::endl;
      passed++;
    }
    else
    {
      std::cout << "[" << i + 1 << "/" << TEST_COUNT << "] " << name << ": FAILED" << std::endl;
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

int main(int argc, char* argv[])
{
  std::cout << "Hello!!!" << std::endl;

  std::cout << "argc=" << argc << std::endl;
  for (int i = 0; i < argc; i++)
  {
    std::cout << "argv[" << i << "]=" << argv[i] << std::endl;
  }

  if ((argc > 1) && (std::strcmp(argv[1], "--ut") == 0))
  {
    return run_ut();
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
