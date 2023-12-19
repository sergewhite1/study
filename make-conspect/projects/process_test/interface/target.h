#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>

#include <vector>
#include <set>

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

class Target
{
  public:
    Target(bool is_phony,
           std::ostream* stream = &std::cout);
    ~Target();

    std::string Name() const { return name_; }
    void SetName(const std::string name);
    void SetStream(std::ostream* stream) { stream_ = stream; }

    void AddPrerequisite(Target* target);
    void Process();

    std::string GraphToStr() const;
    bool IsPhony() const { return isPhony_; }

    bool Exists() const { return exists_; }
    int Ttime() const { return ttime_; }

    bool RunCommands();
    int Touch();

  private:
    static std::set<std::string> NAMES;

    std::string name_;
    std::vector<Target*> prerequisites_;

    bool isPhony_  = false;
    bool exists_   = false;
    int ttime_     = 0;

    std::ostream* stream_;

    void GraphToStr(std::stringstream& ss) const;
};