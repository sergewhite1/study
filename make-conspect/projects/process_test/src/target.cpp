#include "interface/target.h"
#include "interface/time_service.h"

std::set<std::string> Target::NAMES;

Target::Target(bool is_phony,
               std::ostream* stream)
  : isPhony_(is_phony),
    stream_(stream)
{}

Target::~Target()
{
  if (!name_.empty())
  {
    Target::NAMES.erase(name_);
  }
}

void Target::SetName(const std::string name)
{
  if (Target::NAMES.find(name) != Target::NAMES.end())
  {
    throw BadTargetName(name.c_str());
  }

  NAMES.insert(name);
  name_ = name;
}

void Target::AddPrerequisite(Target* target)
{
  prerequisites_.push_back(target);
}

void Target::Process()
{
  bool need_build = true;

  if (!IsPhony() && Exists())
  {
    need_build = false;
  }

  for (auto* prereq : prerequisites_)
  {
    prereq->Process();

    if (prereq->IsPhony())
    {
      need_build = true;
    }
    else
    {
      // Check Prereq Exists
      if (!prereq->Exists())
      {
        if (stream_)
        {
          *stream_ << "File " << prereq->Name() << " does not existing." << std::endl;
          *stream_ << "Stop processing.";
        }
        throw TargetStopProcessing(Name().c_str());
      }

      // Here we are
      if (!Exists())
      {
        need_build = true;
      }
      else if (!(Ttime() > prereq->Ttime()))
      {
        need_build = true;
      }
    }
  }

  if (need_build)
  {
    if (!RunCommands())
    {
      if (stream_)
      {
        *stream_ << "Error in target: " << Name() << std::endl;
        *stream_ << "Stop processing";
      }

      throw TargetStopProcessing(Name().c_str());
    }
  }
  else
  {
    if (stream_)
    {
      *stream_ << "Target " << Name() << " is up to date." << std::endl;
    }
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

std::string Target::GraphToStr() const
{
  std::stringstream ss;
  GraphToStr(ss);
  return ss.str();
}

int Target::Ttime() const
{
  if (Exists() || IsPhony())
  {
    return ttime_;
  }

  throw TimeTargetException(Name().c_str());
}

void Target::GraphToStr(std::stringstream& ss) const
{
  for (const auto * prereq : prerequisites_)
  {
    prereq->GraphToStr(ss);
    ss << Name() << " -> " << prereq->Name() << std::endl;
  }
}

bool Target::RunCommands()
{
  if (stream_)
  {
    *stream_ << "Make target: " << Name() << std::endl;
  }

  if (runCommandsCallBack_)
  {
    runCommandsCallBack_();
  }

  if (!IsPhony() && NeedProduceFile())
  {
    Touch();
  }

  return true;
}

int Target::Touch()
{
  if (IsPhony())
  {
    throw TimeTargetException(Name().c_str());
  }

  exists_ = true;
  ttime_  = TimeService::GetInstance()->UpdateTime();

  return ttime_;
}