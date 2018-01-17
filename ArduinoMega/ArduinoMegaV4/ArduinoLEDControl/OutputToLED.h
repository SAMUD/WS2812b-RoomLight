// OutputToLED.h

#ifndef _OUTPUTTOLED_h
#define _OUTPUTTOLED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "FastLED\FastLED.h"
#include "GlobalVar.h"

#include "GlobalVarLEDControl.h"

//show the LEDs after adding status infos and cropping the Output to the desired size
void OutputToLEDMain();
//Crop the LED Output to fit the Display Mode Left/Right/Night/All
void OutputToLEDDisplayMode();
//Show info-bargraph on the left side of the LED-Strip
void OutputToLEDDisplayInfo();

#endif

