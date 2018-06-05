#include "MyTTime.h"
MyTTime::MyTTime(){
  TimeLast = 0;
  TimeDayDouble = 0;
  TimeDayInt = 0;
  Hour = 0;
}
void MyTTime::UpdateTime(){
	TimeDayDouble = TimeLast/(double)86400000;
	TimeDayInt = TimeLast/86400000;
	Hour = TimeLast/3600000-TimeDayInt*24;
}

