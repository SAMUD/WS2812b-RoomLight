// DisplayEffect.h

#ifndef _DISPLAYEFFECT_h
#define _DISPLAYEFFECT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "FastLED\FastLED.h"
#include "GlobalVar.h"

#include "GlobalVarLEDControl.h"

void DisplayEffectMain();
//Transition
void DisplayEffectTransition();
//Showing all LEDs in white
void DisplayEffectWhite();
//displaying Confetti-Effect
void DisplayEffectConfetti();
void DisplayEffectConfettiColorfull();
//display a marching rainbow
void DisplayEffectRainbowMarch();
//display a Rainbow going back and forth using a sinus curve
void DisplayEffectRainbowBeat();
//testing
void DisplayEffectColorPalBeat();
//filling all the leds with the same color and fading between
void DisplayEffectFade();
void DisplayEffectRGBFade();
void DisplayEffectStrobe();
void DisplayEffectFixedColor();
void DisplayEffectBall();


	

#endif

