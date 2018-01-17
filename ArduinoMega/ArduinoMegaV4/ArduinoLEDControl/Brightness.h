// Brightness.h

#ifndef _BRIGHTNESS_h
#define _BRIGHTNESS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
#include "FastLED\FastLED.h"
#include "GlobalVar.h"

#include "GlobalVarLEDControl.h"

//Fading the Brightness to the Value specified in LEDSetLedBlock.BrightnessSetpoint
void BrightnessFade(uint8_t Setpoint);

//Turning off the LED-Strip
void BrightnessTurnOff();

//Turning on the LED-Strip
void BrightnessTurnOn();



#endif

