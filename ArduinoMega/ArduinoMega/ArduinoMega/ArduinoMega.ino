/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/
#define Version "2.3"
#define DMemoryVersion 9

#include <FastLED.h>
#include "GlobalVar.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

//FastLed-library
#define NUM_LEDS 291
#define DATA_PIN 37
static CRGB leds[NUM_LEDS];
static CRGB ledstemp[NUM_LEDS];

static int i = 0;

// the setup function runs once when you press reset or power the board
void setup()
{
	
	//Setup LEDS
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(0);
	FastLED.setDither(1);

	//Setup serial
	#if defined(DEBUGMODE)
		Serial.begin(115200);
		Serial.print("Starting - App: V");
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
	pinMode(13, OUTPUT);					//Status-Led
	pinMode(PIN_RELAIS, OUTPUT);			//Relais for main power supply
	
	//Prepare EEPROM
	EEPROMinit();

	//Now start the LEDs
	digitalWrite(PIN_RELAIS, 0);
	delay(250);
	SettingsNow.ChangesToEffectMade = true;
	SettingsNow.PowerState = true;

	#ifdef ETHERNET
		ConnectEthernet();
	#endif // ETHERNET
}

// the loop function runs over and over again until power down or reset
void loop()
{
	//reading given IR data (25Hz)
	ReadBinaryMain();

	//we have the Display-Module which runs at full speed and the other Modules which are running one after another.
	EVERY_N_MILLISECONDS(10)
	{
		switch (i)
		{
		case 0:
			//Do all the Ethernet stuff
			#ifdef ETHERNET
			MainEthernet();
			#endif // ETHERNET
			break;
		case 1:
			ReadBinaryMain();
		break;
		case 2:
			if (ReadValues.ButtonPressed == Power && ReadValues.newValues)
			{
				SettingsNow.PowerState = !SettingsNow.PowerState;			//changing PowerState
				if (!SettingsNow.PowerState)
				{
					#if defined(DEBUGMODE)							//initiate PowerOff
					Serial.print("Power button pressed - Turning off: ");
					Serial.println(SettingsNow.PowerState);
					#endif
					EEPROMsave();
					BrightnessTurnOff();
				}
				else
				{
					#if defined(DEBUGMODE)							//initiatePowerOn
					Serial.print("Power button pressed - Turning on: ");
					Serial.println(SettingsNow.PowerState);
					#endif
					BrightnessTurnOn();
					SettingsNow.ChangesToEffectMade = true;
				}
				ReadValues.newValues = 0;
			}
			break;
		case 3:
			//Select Mode - this has to run all the time so we can turn on the LEDs when changing the Mode
			ModeSelectionMain();
			break;
		case 4:
			ChangeParamMain(Down, Up, true, &Settings.LedEffects[Settings.EffectNumber].Saturation, 10, 255, 5, 10);		//Saturation
			break;
		case 5:
			ChangeParamMain(Reward, Forward, true, &Settings.LedEffects[Settings.EffectNumber].Speed, 1, 255, 1, 2);	//SpeedColor
			break;
		case 6:
			ChangeParamMain(VolDown, VolUp, true, &Settings.LedEffects[Settings.EffectNumber].BrightnessSetpoint, 5, 255, 5, 10);		//Brightness
			break;
		case 7:
			if (Settings.LedEffects[Settings.EffectNumber].DisplayMode == Night)					//only do this if current Display mode is set to night
				ChangeParamMain(Zero, StRept, true, &Settings.LedEffects[Settings.EffectNumber].NightNumber, 2, 25, 1, 1);			//Number of LEDs in NightMode
			else
				ChangeParamMain(Zero, StRept, true, &Settings.LedEffects[Settings.EffectNumber].Set, 1, 255, 5, 10);					//Set on the remote
			break;
		case 8:
			TempPlayPauseMain();																			//Play Pause and Color-Temp
		case 9:
			DisplayModeMain();																				//Select Left/Right/Night/all
			break;
		default:
			i = 0;
			break;
		}
		
		i++;
		if (  (i == 10 && SettingsNow.PowerState)  || (i >= 4 && !SettingsNow.PowerState)  )
			i = 0;
	}
	
	//actual power state
	if (SettingsNow.PowerState)
	{
		OutputToLEDMain();
		BlinkLed(10, 3000);
		EVERY_N_MILLISECONDS(20)
		{
			BrightnessFade(Settings.LedEffects[Settings.EffectNumber].BrightnessSetpoint);		//call the fading function for the Brightness
			DisplayEffectMain();

		}
	}
	else
		BlinkLed(3000,2);	
}

