/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/
#define Version "2.3"
#define DMemoryVersion 8

#include <FastLED.h>
#include "GlobalVar.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

//FastLed-library
#define NUM_LEDS 290
#define DATA_PIN 37
static CRGB leds[NUM_LEDS];
static CRGB ledstemp[NUM_LEDS];

//audiobla
#define DC_OFFSET  0                                      // DC offset in mic signal - if unusure, leave 0
														  // I calculated this value by serialprintln lots of mic values
#define NOISE     30                                      // Noise/hum/interference in mic signal and increased value until it went quiet
#define SAMPLES   60                                      // Length of buffer for dynamic level adjustment
#define TOP (NUM_LEDS + 2)                                // Allow dot to go slightly off scale
#define PEAK_FALL 10                                      // Rate of peak falling dot

byte
peak = 0,                                              // Used for falling dot
dotCount = 0,                                              // Frame counter for delaying dot-falling speed
volCount = 0;                                              // Frame counter for storing past volume data
int
vol[SAMPLES],                                               // Collection of prior volume samples
lvl = 10,                                             // Current "dampened" audio level
minLvlAvg = 0,                                              // For dynamic adjustment of graph low & high
maxLvlAvg = 512;




// the setup function runs once when you press reset or power the board
void setup()
{
	//Set Audio
	analogReference(INTERNAL2V56);
	memset(vol, 0, sizeof(vol));
	
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
	pinMode(PINRelais, OUTPUT);

	//Prepare EEPROM
	EEPROMinit();

	Settings.ChangesToEffectMade = 1;
	Settings.PowerState = 1;

	FastLED.setDither(1);

	
#ifdef ETHERNET
	ConnectEthernet();
#endif // ETHERNET

	
}

// the loop function runs over and over again until power down or reset
void loop()
{
	
	//Do all the Ethernet stuff
#ifdef ETHERNET
	MainEthernet();
#endif // ETHERNET

	//reading given data (25Hz)
	ReadBinaryMain();

	//turn on/off
	EVERY_N_MILLISECONDS(100) //only every 100ms because the values from the other arduino are only aquired at this speed
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
				digitalWrite(PINRelais, 0);
			}
			else
			{
				#if defined(DEBUGMODE)							//initiatePowerOn
				Serial.print("Power button pressed - Turning on: ");
				Serial.println(Settings.PowerState);
				#endif
				digitalWrite(PINRelais, 1);
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

