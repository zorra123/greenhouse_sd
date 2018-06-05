#include "Card.h"

Card::Card()
{
	//&&(int)TxtRead[i+1]>57&&(int)TxtRead[i+1]<48
}


/*
day,temp,hum,ground_temp,solution,hum_seed,light
[0,3],[18,20],70,[19,21],[99,100],20;
[4,6],[18,20],70,[19,21],[99,100],24;
[7,10],[18,20],70,[19,21],[99,100],18;
[11,17],[18,20],70,[19,21],[99,100],16;

 */
void Card::CheckStage(MyTTime &TimeNew){
	if(TimeNew.TimeDayDouble>=stage){
		stage++;
		RreadStage(stage,TimeNew);
	}
}
void Card::CheckLight(uint8_t hour){
	if(hour>=light)		digitalWrite(8, HIGH);
	else digitalWrite(8, LOW);
}
void Card::Parse(char* TxtRead,uint8_t len)
{
	byte tmp[10]={0};
	for (int i=0,j=0;i<len;i++)
	{
		if(((int)TxtRead[i])>=48&&((int)TxtRead[i])<=57)
		{

			tmp[j] += TxtRead[i]-48;

	 // Serial.print(tmp[j]);
			if(((int)TxtRead[i+1])>57||((int)TxtRead[i+1])<48){
				j++;
			}
			else{
				tmp[j]*=10;
			}
		}
	}

	day[0]=tmp[0];
	day[1]=tmp[1];
	temp[0]=tmp[2];
	temp[1]=tmp[3];
	hum=tmp[4];
	ground_temp[0]=tmp[5];
	ground_temp[1]=tmp[6];
	hum_seed[0]=tmp[7];
	hum_seed[1]=tmp[8];
	light=tmp[9];
}
void Card::Parse(char* TxtRead,uint8_t len,unsigned long* TimeTmp ){
	unsigned long tmp[2]={0};
	for (int i=0,j=0;i<len;i++)
	{
		if(((int)TxtRead[i])>=48&&((int)TxtRead[i])<=57)
		{

			tmp[j] += TxtRead[i]-48;
			if(((int)TxtRead[i+1])>57||((int)TxtRead[i+1])<48){
				j++;
			}
			else{
				tmp[j]*=10;
			}
		}
	
	}
	stage = (int)tmp[0];
	TimeTmp = tmp[1];
	ReadFromPlant(stage);
}
void Card::ReadFromPlant(uint8_t number){
		stage = number;
		String TxtRead;
		myFile = SD.open("plant1.txt");
		while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
		}
		if (!SD.begin(4)) {
			Serial.println("initialization failed!");
			return;
		}
		byte count = 0;
		while(myFile.available())
		{
			char symbol = (char)myFile.read();
			if(count==number)
		{	
				TxtRead += symbol;
		}
		  else if(count>number)
		{
		  break;  
		}
		if(symbol=='\n')
		 count++;
		}
		myFile.close();
		char tmp[TxtRead.length()];

		TxtRead.toCharArray(tmp, TxtRead.length());
		Parse(tmp,TxtRead.length());
}
void Card::RreadStage(uint8_t number,MyTTime &TimeNew)
{
	myFile = SD.open("log.txt");
	if(!myFile.available()){
		myFile.close();
		ReadFromPlant(number);
	}
	else{
		String TxtRead;
		while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
		}
		if (!SD.begin(4)) {
			Serial.println("initialization failed!");
			return;
		}
		while(myFile.available()){
		
			char symbol = (char)myFile.read();
			TxtRead += symbol;
		}
		myFile.close();
		char tmp[TxtRead.length()];

		TxtRead.toCharArray(tmp, TxtRead.length());
		Parse(tmp,TxtRead.length(),TimeNew.TimeLast);		
	}
}
void Card::Write(MyTTime &TimeNew)
{
	SD.remove("log.txt");
	myFile = SD.open("log.txt",FILE_WRITE);
	if (myFile) {
		myFile.print(stage);
		myFile.print(",");
		if(TimeNew.TimeLast<millis()){
			myFile.println(millis());
		}
		else{
			TimeNew.TimeLast += 3600000;
			myFile.println(TimeNew.TimeLast);
		}
		// close the file:
		myFile.close();
		//Serial.println("done.");
	} 
		else {
		// if the file didn't open, print an error:
			Serial.println("error opening test.txt");
		}
}
