#pragma once

#include <sstream>
#include <stdexcept>

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