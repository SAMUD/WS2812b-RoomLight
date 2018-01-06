/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/
#define Version "2.3"
#define DMemoryVersion 8

#include <FastLED.h>;
#include "GlobalVar.h"
#include <SPI.h>
#include <Ethernet.h>
#include <EthernetUdp.h>





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
	LEDBlockSetup();
	
	//Set Audio
	analogReference(INTERNAL2V56);
	memset(vol, 0, sizeof(vol));
	
	//Setup LEDS
	

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
			#if defined(DEBUGMODE)
			if (LEDBlockSetOnOffToggle())
				Serial.print("IR: Turned it on");
			else
				Serial.print("IR: Turned it off");
			#else
			LEDBlockSetOnOffToggle();
			#endif
		}	
	}

	//Select Mode - this has to run all the time so we can turn on the LEDs when changing the Mode
	ModeSelectionMain();

	//actual power state
	if (LEDBlockGetOnOffState())
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

		
		LEDBlockLoop();
		

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

