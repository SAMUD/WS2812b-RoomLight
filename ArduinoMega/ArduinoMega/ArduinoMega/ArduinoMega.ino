/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/
# define Version "2.1"
#define DMemoryVersion 6

#include <FastLED.h>
#include "GlobalVar.h"

//FastLed-library
#define NUM_LEDS 291
#define DATA_PIN 51
static CRGB leds[NUM_LEDS];
static CRGB ledstemp[NUM_LEDS];



// the setup function runs once when you press reset or power the board
void setup()
{
	//Setup LEDS
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(0);

	//Setup serial
	#if defined(DEBUGMODE)
		Serial.begin(115200);
		Serial.print("Started - Waiting - App: V");
		Serial.println(Version);
		Serial.print("LED Library: V");
		Serial.println(FASTLED_VERSION);
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

	//Prepare EEPROM
	EEPROMinit();

	Settings.ChangesToEffectMade = 1;
	Settings.PowerState = 1;

	FastLED.setDither(1);

}

// the loop function runs over and over again until power down or reset
void loop()
{
	
	//reading given data (25Hz)
	ReadBinaryMain();

	//turn on/off
	EVERY_N_MILLISECONDS(100) //only every 40ms because the values from the other arduino are only aquired at this speed
	{
		if (ReadValues.ButtonPressed == Power && ReadValues.newValues)
		{
			Settings.PowerState = !Settings.PowerState;
			if (!Settings.PowerState)
			{
				#if defined(DEBUGMODE)
					Serial.print("Power button pressed - Turning off: ");
					Serial.println(Settings.PowerState);
				#endif
				EEPROMsave();
				BrightnessTurnOff();
				
			}
			else
			{
				#if defined(DEBUGMODE)
					Serial.print("Power button pressed - Turning on: ");
					Serial.println(Settings.PowerState);
				#endif
				BrightnessTurnOn();
				Settings.ChangesToEffectMade = 1;
			}
			ReadValues.newValues = 0;
		}
	}

	//Select Mode
	ModeSelectionMain();

	//actual power state
	if (Settings.PowerState)
	{
		//LEDs are on
		
		//ChangeSpeed
		ForwardBackwardMain();

		//set night number
		NightNumberMain();

		//Select Left/Right/Night/all
		DisplayModeMain();

		//Change Saturation
		SaturationMain();

		//Display Effect
		DisplayEffectMain();

		//Change Brightness
		BrightnessMain();

		//Change Colors
		TempPlayPauseMain();

		//print out
		OutputToLEDMain();

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

