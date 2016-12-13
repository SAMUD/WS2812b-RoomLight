/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/

#include <FastLED.h>
#include "GlobalVar.h"



//FastLed-library
#define NUM_LEDS 291
#define DATA_PIN 51
CRGB leds[NUM_LEDS];



// the setup function runs once when you press reset or power the board
void setup()
{
	//Setup LEDS
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(0);
	set_max_power_in_volts_and_milliamps(5, 200);

	//Setup serial
	#if defined(DEBUGMODE)
	Serial.begin(115200);
	Serial.println("Started - Waiting - V1.0");
	#endif
	//Setting Pin-Modes
	pinMode(PINValueChanged, INPUT);
	pinMode(PINMultiplePresses, INPUT);
	pinMode(PINInput1, INPUT);
	pinMode(PINInput2, INPUT);
	pinMode(PINInput3, INPUT);
	pinMode(PINInput4, INPUT);
	pinMode(PINInput5, INPUT);
	pinMode(13, OUTPUT);

	//[Temp] this part is only needed until I will implement the EEPROM-Code to save settings
	LEDSettings.BrightnessSetpoint=50;
	LEDSettings.PowerState = 1;
	LEDSettings.DisplayMode = WhiteAll;
	LEDSettings.DisplayModeOld = None;
	LEDSettings.ChangesToEffectMade = 1;
	LEDSettings.Temperature = Tungsten100W2;
	LEDSettings.PlayPause = 1;
	LEDSettings.SpeedMultiplikator = 4;
	LEDSettings.Saturation = 255;
}

// the loop function runs over and over again until power down or reset
void loop()
{
	
	//reading given data
	ReadBinaryMain();

	//turn on/off
	EVERY_N_MILLISECONDS(50) //only every 50ms because the values from the other arduino are only aquired at this speed
	{
		if (ReadValues.ButtonPressed == Power && ReadValues.newValues)
		{
			LEDSettings.PowerState = !LEDSettings.PowerState;
			if (!LEDSettings.PowerState)
			{
				#if defined(DEBUGMODE)
				Serial.println("Power button pressed - Turning off");
				#endif
				BrightnessTurnOff();
				
			}
			else
			{
				#if defined(DEBUGMODE)
				Serial.println("Power button pressed - Turning on");
				#endif
				BrightnessTurnOn();
				LEDSettings.ChangesToEffectMade = 1;
			}
			ReadValues.newValues = 0;
		}
	}
	//Select Mode
	ModeSelectionMain();

	//actual power state
	if (LEDSettings.PowerState)
	{
		//LEDs are on
		
		//ChangeSpeed
		ForwardBackwardMain();

		//Change Saturation
		//SaturationMain();

		//Display Effect
		DisplayEffectMain();

		//Change Brightness
		BrightnessMain();

		//Change Colors
		TempPlayPauseMain();

		//print out
		FastLED.show();
		//show_at_max_brightness_for_power();

		//Status LED on Arduino Board
		BlinkLed(10, 3000);
	}
	else
	{
		//LEDs are off
		//Blink Status LED on Arduino Board
		BlinkLed(3000,2);
	}

	//no new values anymore.
		
}

