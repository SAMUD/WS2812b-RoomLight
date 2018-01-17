// GlobalVarLEDControl.h

#ifndef _GLOBALVARLEDCONTROL_h
#define _GLOBALVARLEDCONTROL_h

#include "MyTypes.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "FastLED.h"

//////////////////////////////////
//       USER SECTION           //
//////////////////////////////////

#define NUM_LEDS_max 500		//Number of Maximum LEDs supprted with this Class. Pay attention, that increasing this number increases the storage used!
#define DATA_PIN 37				//Hardware Pin where the LEDs are plugged
#define PIN_RELAIS 53			//Output to the Relais --> enable Power to LEDs

#define NUM_LEDS_Left 108
#define NUM_LEDS_Right 96

//////////////////////////////////
//      END USER SECTION        //
//////////////////////////////////

#define Version "1.0"
#define DMemoryVersion 1

static CRGB _leds[NUM_LEDS_max];
static CRGB _ledstemp[NUM_LEDS_max];

/// <summary>
/// All Settings for LEDs. This one will also be saved in EEPROM.
/// </summary>
static struct StoreStruct
{
	uint8_t MemoryVersion;
	ModeSetLedBlock FixedColor[3];
	ModeSetLedBlock White[2];
	ModeSetLedBlock Confetti[1];
	ModeSetLedBlock RainbowMarch;
	ModeSetLedBlock RainbowBeat;
	ModeSetLedBlock ColorPalBeat;
	ModeSetLedBlock Fade;
	ModeSetLedBlock RGBFade;
	ModeSetLedBlock Strobe;
	ModeSetLedBlock Ball;

	ModeSetLedBlock *Current;
	ModeSetLedBlock *CurrentOLD;

}Settings;

/// <summary>
/// Volatile Settings and Information Bytes
/// </summary>
static struct sDisplayInfo
{
	bool ShowACK;				//Turning on the ACK-Light
	uint8_t ShowPercentage;		//Show setting Percentage
	bool DebuggingOn = false;	//Turn on debugging in this Module
	bool PowerState;			//true=On False=off
	bool ChangesToEffectMade;	//when the LEDS need to be redrwan, cause there were changes to the effects 
	bool PlayPause;
}SettingsNow;

#endif

