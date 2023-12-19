#include "interface/time_service.h"

TimeService* TimeService::instance_ = nullptr;

TimeService* TimeService::GetInstance()
{
  if (instance_ == nullptr)
  {
    instance_ = new TimeService();
  }

  return instance_;
}

void TimeService::Release()
{
  delete instance_;
  instance_ = nullptr;
}