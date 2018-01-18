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
	

	LedControlClass();

	void Init(int NumberLEDs, bool SetDither);

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
	void SetNewMode(int Effect);
	//decrease/increase brightness

	bool GetOnOffState();
	bool GetPauseState();
	uint8_t GetBrightness();
	int GetMode();
	
	ColTemp GetTemp();

private:
	void OutputToLed();
	void DisplayEffectMain();
	//Transition
	void DisplayEffectTransition();
	//Showing all LEDs in white
	void DisplayEffectWhite();
	//displaying Confetti-Effect
	void DisplayEffectConfetti();
	void DisplayEffectConfettiColorfull();
	//display a marching rainbow
	void DisplayEffectRainbowMarch();
	//display a Rainbow going back and forth using a sinus curve
	void DisplayEffectRainbowBeat();
	//testing
	void DisplayEffectColorPalBeat();
	//filling all the leds with the same color and fading between
	void DisplayEffectFade();
	void DisplayEffectRGBFade();
	void DisplayEffectStrobe();
	void DisplayEffectFixedColor();
	void DisplayEffectBall();
	//Fading the Brightness to the Value specified in LEDSetLedBlock.BrightnessSetpoint
	void BrightnessFade(uint8_t Setpoint);

	//Turning off the LED-Strip
	void BrightnessTurnOff();

	//Turning on the LED-Strip
	void BrightnessTurnOn();
};

extern LedControlClass LedControl;

#endif

