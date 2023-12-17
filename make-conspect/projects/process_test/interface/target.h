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