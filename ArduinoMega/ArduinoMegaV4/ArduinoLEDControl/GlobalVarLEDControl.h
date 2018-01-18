// GlobalVarLEDControl.h

#ifndef _GLOBALVARLEDCONTROL_h
#define _GLOBALVARLEDCONTROL_h

#include "MyTypes.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "FastLED\FastLED.h"
#include "GlobalVar.h"

//////////////////////////////////
//       USER SECTION           //
//////////////////////////////////

#define NUMleds_max 300		//Number of Maximum LEDs supprted with this Class. Pay attention, that increasing this number increases the storage used!
#define DATA_PIN 37				//Hardware Pin where the LEDs are plugged
#define PIN_RELAIS 53			//Output to the Relais --> enable Power to LEDs

#define NUMleds_Left 108
#define NUMleds_Right 96

//////////////////////////////////
//      END USER SECTION        //
//////////////////////////////////

#define ClassVersion "1.0"
#define DMemoryVersion 6

#define NUMBEREFFECTS 15

static CRGB leds[NUMleds];
static CRGB ledstemp[NUMleds];

/// <summary>
/// All Settings for LEDs. This one will also be saved in EEPROM.
/// </summary>
static struct StoreStruct
{
	uint8_t MemoryVersion;
	ModeSetLedBlock LedEffects[NUMBEREFFECTS];

	uint8_t EffectNumber=0;
	uint8_t EffectNumberOld=127;

}Settings;

/// <summary>
/// Volatile Settings and Information Bytes
/// </summary>
static struct sDisplayInfo
{
	bool ShowACK;				//Turning on the ACK-Light
	uint8_t ShowPercentage;		//Show setting Percentage
	bool PowerState;			//true=On False=off
	bool ChangesToEffectMade;	//when the LEDS need to be redrwan, cause there were changes to the effects 
	bool PlayPause;
}SettingsNow;

#endif

