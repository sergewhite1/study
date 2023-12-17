#include "interface/time_service.h"

int TimeService::CURRENT_TIME = 0;

void TimeService::SetTime(int value)
{
  if (!(TimeService::GetCurrentTime() < value))
  {
    throw TimeServiceException(TimeService::GetCurrentTime(), value);
  }

  TimeService::CURRENT_TIME = value;
}