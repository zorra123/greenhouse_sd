#include <Metro.h> 
#include "String.h"
#include "Card.h"
#include "MyTTime.h"
Metro MetroHour = Metro(3600000);
MyTTime TimeNew; 
Card Sd;

void setup(void)
{
	Serial.begin(9600);
	//MsTimer2::set(5000, function); // ������ 5 � �������� �������, ���������� ���������� � �������� � ����������
								   // JSON � Serial.
	pinMode(3, OUTPUT);
	pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
	digitalWrite(3, LOW);//вентиляторы
	digitalWrite(8, LOW);//свет
  digitalWrite(9, HIGH);//насос
  Sd.RreadStage(1,TimeNew);
  if(TimeNew.TimeLast!=0)
    Sd.Write(TimeNew);
}

void loop(void) {
  if (MetroHour.check() == 1){
       Sd.Write(TimeNew);
       TimeNew.UpdateTime();
       Sd.CheckLight(TimeNew.Hour);
       Sd.CheckStage(TimeNew);
  }
  
	
}

