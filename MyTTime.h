#pragma once
#include <Arduino.h>
class MyTTime{
public:
  MyTTime();
  unsigned long TimeLast;
  double TimeDayDouble;
  uint8_t TimeDayInt;
  uint8_t Hour;
  void UpdateTime();
};

