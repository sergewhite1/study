#pragma once

// Singelton (not MT safe!)
class TimeService
{
  public:
    static TimeService* GetInstance();
    static void Release();

    int  GetCurrentTime() { return currentTime_; }
    int UpdateTime() { return ++currentTime_; }
    void SetTime(int value) { currentTime_ = value; }

  protected:
    TimeService() = default;

  private:
    static TimeService* instance_;
    int currentTime_ = 0;
};