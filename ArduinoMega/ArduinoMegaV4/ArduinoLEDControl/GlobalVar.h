// GlobalVar.h

#ifndef _GLOBALVAR_h
#define _GLOBALVAR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

	//define different options
	#define DEBUGMODE
	//#define ETHERNET
#define Version "1.0"

	//In Out Pins used on my Arduino
	#define PINValueChanged 36
	#define PINMultiplePresses 34
	#define PINInput1 30						//The LSB-Bit coming from the other Arduino
	#define PINInput2 28
	#define PINInput3 26
	#define PINInput4 24
	#define PINInput5 22						//The MSB-Bit coming from the other Arduino
	#define MIC_PIN   A0						// Microphone is attached to this analog pin
	#define NUMleds 290				

	//The Buttons which are availaible on my Transmitter
	/*	Zero=
	One=
	Two=		effect modes like Confetti+Strobe
	Three=
	Four=
	Five=		fading, butt all leds have the same color
	Six=		turn on white
	Seven=		fixed color
	Eight=		fading modes with different colors for each LED
	Nine=		turn all leds on at full brightness even when other settings where specified before
	Power=		Turn the strip on/off
	VolUp=		Brightness+
	FuncStop=	change Between Modes --> All,Left,Right,Night
	Reward=		slow down effects / previous color
	PlayPause=	in WhiteModes: Temperature | else: PlayPause
	Forward=	Speed up effects / next color
	Down=		Sturation -
	VolDown=	Brightness-
	Up=			Saturation +
	Eq=
	StRept=
	Nothing=	Enum default state at bootup
	*/



enum Buttons
{
	Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
	Power, VolUp, FuncStop, Reward, PlayPause, Forward, Down, VolDown, Up, Eq, StRept,
	Nothing
};

//structure with the values read from the other Arduino
static struct Values
{
	Buttons ButtonPressed;
	bool Repeat;
	bool newValues;
}ReadValues;

#endif

