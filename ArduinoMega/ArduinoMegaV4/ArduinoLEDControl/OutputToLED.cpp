// 
// 
// 

#include "OutputToLED.h"
#include "FastLED\FastLED.h"
#include "GlobalVar.h"

#include "GlobalVarLEDControl.h"

//show the LEDs after adding status infos and cropping the Output to the desired size
void OutputToLEDMain()
{
	memmove(&_leds[0], &_ledstemp[0], NUM_LEDS * sizeof(CRGB));
	OutputToLEDDisplayMode(); //crop the LED-Output
	OutputToLEDDisplayInfo(); //show button pressed info

	FastLED.show();
}

//Crop the LED Output to fit the Display Mode Left/Right/Night/All
void OutputToLEDDisplayMode()
{
	static uint16_t dot = 0;
	if (Settings.Current->DisplayMode == Left)
		fill_solid(&_leds[NUM_LEDS_Left], NUM_LEDS - NUM_LEDS_Left, CHSV(0, 0, 0));
	if (Settings.Current->DisplayMode == Right)
		fill_solid(_leds, NUM_LEDS - (NUM_LEDS_Right - 1), CHSV(0, 0, 0));
	if (Settings.Current->DisplayMode == Night)
	{
		for (dot = 0; dot < NUM_LEDS; dot = dot + 1)
		{
			if (dot%Settings.Current->NightNumber)
				_leds[dot] = CRGB::Black;
		}
	}
}

//Show info-bargraph on the left side of the LED-Strip
void OutputToLEDDisplayInfo()
{
	static uint8_t counter = 0;

	//if the state of the variable to show infos on the LEDs went true
	if (SettingsNow.ShowACK)
	{
		counter = 25;
		SettingsNow.ShowACK = 0;
		if (SettingsNow.DebuggingOn)
			Serial.println("OutputToLED | DisplayInfo updated ");
	}

	if (counter > 0)
	{
		//display info
		if (SettingsNow.ShowPercentage > 0)
		{
			fill_solid(_leds, SettingsNow.ShowPercentage / 10, CRGB::Green);
			fill_solid(&(_leds[SettingsNow.ShowPercentage / 10]), 25 - (SettingsNow.ShowPercentage / 10), CRGB::Black);
			_leds[25] = CRGB::Red;
		}
		else
		{
			_leds[1] = CRGB::Green;
			_leds[2] = CRGB::Red;
		}
		_leds[0] = CRGB::Red;

		//decrease the counter-display time
		EVERY_N_MILLISECONDS(100)
		{
			counter = counter - 1;
			if (counter == 0)
				SettingsNow.ShowPercentage = 0;
		}

	}
}
