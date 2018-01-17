/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/


#ifndef LEDControl.h
#include "./Code/LEDClass/LEDControl.h";
#endif
#ifndef GlobalVar.h
#include "GlobalVar.h";
#endif


LEDControl myLEDs(NUM_LEDS, 0, true, true);


// the setup function runs once when you press reset or power the board
void setup()
{
}

// the loop function runs over and over again until power down or reset
void loop()
{
	myLEDs.Loop();
}

