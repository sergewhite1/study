#pragma once

#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <vector>
#include <set>

class TargetExeption : public std::runtime_error
{
  public:
    TargetExeption(const char* target_name)
    : std::runtime_error("Target Exception")
    {
      targetName_.append(target_name);
      message_ = "Target Exception. Target Name: " + targetName_;
    }

    // std::exception interface
    virtual const char* what() const noexcept
    {
      return message_.c_str();
    }

    std::string TargetName() const { return targetName_; }

  protected:
    std::string message_;

  private:
    std::string targetName_;
};

class BadTargetName : public TargetExeption
{
  public:
    BadTargetName(const char* target_name)
    : TargetExeption(target_name)
    {
      message_ = std::string("Bad Target Name: ") + std::string(target_name);
    }
};

class TargetStopProcessing : public TargetExeption
{
  public:
    TargetStopProcessing(const char* target_name)
    : TargetExeption(target_name)
    {
      message_ = std::string("TargetStopProcessing. Name: ") +
                 std::string(target_name);
    }
};

class TimeTargetException : public TargetExeption
{
  public:
    TimeTargetException(const char* target_name)
    : TargetExeption(target_name)
    {
      message_ =
        std::string("TimeTargetException. Target is not phony and does not exist! TargetName: ") +
        std::string(target_name);
    }
};

class Target
{
  public:
    //using RunCommandsCallBack_t = void(*)();
    using RunCommandsCallBack_t = std::function<void()>;

    static constexpr int INVALID_TIME = -1;

    Target(bool is_phony,
           std::ostream* stream = &std::cout);
    ~Target();

    std::string Name() const { return name_; }
    void SetName(const std::string name);
    void SetStream(std::ostream* stream) { stream_ = stream; }
    void SetRunCommandsCallBack(Target::RunCommandsCallBack_t callback)
    {
      runCommandsCallBack_ = callback;
    }

    void AddPrerequisite(Target* target);
    void Process();

    std::string GraphToStr() const;
    bool IsPhony() const { return isPhony_; }

    bool Exists() const { return exists_; }
    int Ttime() const;

    bool RunCommands();
    int Touch();

  private:
    static std::set<std::string> NAMES;

    std::string name_;
    std::vector<Target*> prerequisites_;

    bool isPhony_  = false;
    bool exists_   = false;
    int ttime_     = Target::INVALID_TIME;

    std::ostream* stream_;

    RunCommandsCallBack_t runCommandsCallBack_;

    void GraphToStr(std::stringstream& ss) const;
};