#pragma once
#include "String.h"
#include "MyTTime.h"
#include <SPI.h>
#include <SD.h>
class Card{
public:
	//construct
	Card();
	//???? ?????? ?? ???? ????????
	void RreadStage(uint8_t,MyTTime &TimeNew);
	void Write(MyTTime &TimeNew);
	void CheckLight(uint8_t);
	void CheckStage(MyTTime &TimeNew);
private:
  File myFile;
	//String TxtRead;
	uint8_t stage;
	uint8_t day[2];
	uint8_t temp[2];
	uint8_t hum;
	uint8_t ground_temp[2];
	uint8_t hum_seed[2];
	uint8_t light;
	void Parse(char *,uint8_t);
	void Parse(char* ,uint8_t ,unsigned long*);
	void ReadFromPlant(uint8_t );
};

