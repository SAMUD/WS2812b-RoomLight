/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/
#define Version "2.2"
#define DMemoryVersion 7

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
			Settings.PowerState = !Settings.PowerState;			//changing PowerState
			if (!Settings.PowerState)
			{
				#if defined(DEBUGMODE)							//initiate PowerOff
				Serial.print("Power button pressed - Turning off: ");
				Serial.println(Settings.PowerState);
				#endif
				EEPROMsave();
				BrightnessTurnOff();	
			}
			else
			{
				#if defined(DEBUGMODE)							//initiatePowerOn
				Serial.print("Power button pressed - Turning on: ");
				Serial.println(Settings.PowerState);
				#endif
				BrightnessTurnOn();
				Settings.ChangesToEffectMade = 1;
			}
			ReadValues.newValues = 0;
		}
	}

	//Select Mode - this has to run all the time so we can turn on the LEDs when changing the Mode
	ModeSelectionMain();

	//actual power state
	if (Settings.PowerState)
	{
		//reaing data from IR-remote and changing settings
		EVERY_N_MILLISECONDS(100)
		{
			ChangeParamMain(Down, Up, true, &Settings.Current.Saturation, 10, 255, 5, 10);					//Saturation
			ChangeParamMain(Reward, Forward, true, &Settings.Current.SpeedColor, 1, 255, 1, 2);				//Speed or Color
			if(Settings.Current.DisplayMode == Night)					//only do this if current Display mode is set to night
				ChangeParamMain(Zero, StRept, true, &Settings.Current.NightNumber, 2, 25, 1, 1);			//Number of LEDs in NightMode
			else
				ChangeParamMain(Zero, StRept, true, &Settings.Current.Set, 1, 255, 5, 10);					//Set on the remote
			ChangeParamMain(VolDown, VolUp, true, &Settings.Current.BrightnessSetpoint, 5, 255, 5, 10);		//Brightness
			
			DisplayModeMain();																				//Select Left/Right/Night/all
			TempPlayPauseMain();																			//Play Pause and Color-Temp
				
		}

		EVERY_N_MILLISECONDS(40)
		{
			BrightnessFade(Settings.Current.BrightnessSetpoint);		//call the fading function for the Brightness
		}

		//Display Effect
		DisplayEffectMain();

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

