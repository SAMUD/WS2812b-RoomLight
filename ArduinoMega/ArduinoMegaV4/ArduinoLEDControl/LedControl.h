// LedControl.h

#ifndef _LEDCONTROL_h
#define _LEDCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


#include "LedControl.h"
#include "GlobalVarLEDControl.h"

class LedControlClass
{
public:
	
	//Konstructor
	

	LedControlClass(int NumberLEDs, bool SetDither);

	//Running the main Loop
	void Loop();


	//Set and Get all those settings
	void SetOnOff(bool NewState);
	bool ToggleOnOff();
	void SetPause(bool NewState);
	bool TogglePause();
	void SetBrightness(uint8_t NewValue);
	void SetNightNumber(uint8_t NewValue); //only allowed when in the righ display mode
	//increase / decrease night number
	void SetDisplayMode(eDisplay NewValue);
	void SetNextDisplayMode();
	void SetSaturation(uint8_t NewValue);
	//increase decrease saturation
	void SetSet(uint8_t NewValue);
	//increase / decrease set
	void SetSpeed(uint8_t NewValue);
	//icrease decrease speed
	void SetTemp(ColTemp NewValue);
	void SetNextTemp();
	void SetNewMode(String Mode);
	void LEDBlockSetBrightness(uint8_t NewValue);
	//decrease/increase brightness

	bool GetOnOffState();
	bool GetPauseState();
	//get current mode (white/rainbow etc)
	ColTemp GetTemp();
};

extern LedControlClass LedControl;

#endif

