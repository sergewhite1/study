#include "interface/target.h"
#include "interface/time_service.h"

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