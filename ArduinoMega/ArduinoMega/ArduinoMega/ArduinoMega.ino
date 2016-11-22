/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/

#include "GlobalVar.h"
#include <FastLED.h>

#define NUM_LEDS 8
#define DATA_PIN 51

CRGB leds[NUM_LEDS];



// the setup function runs once when you press reset or power the board
void setup() {
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(0);

	Serial.begin(9600);
	Serial.println("Started - Waiting - V1.0");

	pinMode(PINValueChanged, INPUT);
	pinMode(PINMultiplePresses, INPUT);
	pinMode(PINInput1, INPUT);
	pinMode(PINInput2, INPUT);
	pinMode(PINInput3, INPUT);
	pinMode(PINInput4, INPUT);
	pinMode(PINInput5, INPUT);
	pinMode(13, OUTPUT);

	//this part is only needed until I will implement the EEPROM-Code to save settings
	LEDSettings.BrightnessSetpoint=128;
	LEDSettings.PowerState = 1;
	LEDSettings.DisplayMode = WhiteAll;
}

// the loop function runs over and over again until power down or reset
void loop() {
	
	//reading given data
	ReadBinaryMain();

	//Select display mode
	ModeSelectionMain();

	//turn on/off
	if (ReadValues.ButtonPressed == Power && ReadValues.newValues)
	{
		Serial.println("Power button pressed");
		LEDSettings.PowerState = !LEDSettings.PowerState;
		

		if (!LEDSettings.PowerState)
			//turning off
			BrightnessTurnOff();
		else
			BrightnessTurnOn();
	}

	//actual power state
	if (LEDSettings.PowerState)
	{
		//LEDs are on
		
		DisplayEffectMain();

		BrightnessMain();

		HueSaturationMain();

		FastLED.show();

		BlinkLed(10, 3000);
	}
	else
	{
		//LEDs are off
		BlinkLed(3000,2);
	}

	//no new values anymore.
	ReadValues.newValues = 0;	
	
}

