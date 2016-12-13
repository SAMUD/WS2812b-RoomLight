

void DisplayEffectMain()
{
	if (LEDSettings.DisplayMode != LEDSettings.DisplayModeOld)
	{
		DisplayEffectTransition();
		LEDSettings.DisplayModeOld = LEDSettings.DisplayMode;
		LEDSettings.ChangesToEffectMade = 1;
	}

	//Select the right effect from the list
	if (LEDSettings.DisplayMode == WhiteAll && LEDSettings.ChangesToEffectMade)
		DisplayEffectWhiteAll();
	else if (LEDSettings.DisplayMode == WhiteLeft && LEDSettings.ChangesToEffectMade)
		DisplayEffectWhiteLeft();
	else if (LEDSettings.DisplayMode == WhiteRight && LEDSettings.ChangesToEffectMade)
		DisplayEffectWhiteRight();
	else if (LEDSettings.DisplayMode == Confetti && LEDSettings.ChangesToEffectMade  && LEDSettings.PlayPause)
		DisplayEffectConfetti();
	else if (LEDSettings.DisplayMode == RainbowMarch && LEDSettings.ChangesToEffectMade  && LEDSettings.PlayPause)
		DisplayEffectRainbowMarch();
	else if (LEDSettings.DisplayMode == RainbowBeat && LEDSettings.ChangesToEffectMade  && LEDSettings.PlayPause)
		DisplayEffectRainbowBeat();
	else if (LEDSettings.DisplayMode == ColorPalBeat && LEDSettings.ChangesToEffectMade && LEDSettings.PlayPause)
		DisplayEffectColorPalBeat();
	else if (LEDSettings.DisplayMode == Fade && LEDSettings.ChangesToEffectMade && LEDSettings.PlayPause)
		DisplayEffectFade();
	else if (LEDSettings.DisplayMode == RGBFade && LEDSettings.ChangesToEffectMade && LEDSettings.PlayPause)
		DisplayEffectRGBFade();
	else if (LEDSettings.DisplayMode == ConfettiColorfull && LEDSettings.ChangesToEffectMade && LEDSettings.PlayPause)
		DisplayEffectConfettiColorfull();
	else if (LEDSettings.DisplayMode == Strobe && LEDSettings.ChangesToEffectMade && LEDSettings.PlayPause)
		DisplayEffectStrobe();
	else if (LEDSettings.DisplayMode == Night && LEDSettings.ChangesToEffectMade)
		DisplayEffectNight();

	
}

//Transition
void DisplayEffectTransition()
{

}

//Showing all LEDs in white
void DisplayEffectWhiteAll()
{
	fill_solid(leds, NUM_LEDS, LEDSettings.Temperature);
	LEDSettings.ChangesToEffectMade = 0;
}

//Showing only the left side in white
void DisplayEffectWhiteLeft()
{
	float temp;
	uint8_t temp2;

	fill_solid(leds, NUM_LEDS, CHSV(0, 0, ValueLEDDarkside));
	fill_solid(leds, NumberLEDLeft, LEDSettings.Temperature);
	

	LEDSettings.ChangesToEffectMade = 0; //no periodically changes needed
}

//Showing only the right side in white
void DisplayEffectWhiteRight()
{
	for (int dot = 1; dot <= NUM_LEDS; dot++)
	{
		if (dot < NumberLEDRight)
			leds[NUM_LEDS - dot] = LEDSettings.Temperature;
		else
			leds[NUM_LEDS - dot] = CHSV(0,0, ValueLEDDarkside);
	}
	LEDSettings.ChangesToEffectMade = 0; //no periodically changes needed

}

//displaying Confetti-Effect
void DisplayEffectConfetti()
{
	#define huediff 510													
	static int					thishue = 0;                               // Starting hue.
	static int8_t				thisinc = 3;                               // Incremental value for rotating hues
	
	uint8_t secondHand = (millis() / 1000) % 15;							// Change '15' to a different value to change duration of the loop.
	static uint8_t lastSecond = 99;								
	
	if (lastSecond != secondHand) 
	{							
		lastSecond = secondHand;
		switch (secondHand) {
		case  0: thisinc = 0; break; 
		case  5: thisinc = 3; break;
		case 10: thisinc = 1; break;      
		case 15: thisinc = 1; break;																	
		}
	}

	EVERY_N_MILLISECONDS(40) 
	{								
		fadeToBlackBy(leds, NUM_LEDS, beatsin8(5,LEDSettings.SpeedMultiplikator/2,LEDSettings.SpeedMultiplikator*2));         
		int pos = random16(NUM_LEDS);									// Pick an LED at random.
		leds[pos] += CHSV((thishue+random16(huediff))/4, 255, 255);		
		thishue = thishue + thisinc;
	}

	LEDSettings.ChangesToEffectMade = 1; //periodic update needed
}

void DisplayEffectConfettiColorfull()
{
	#define huediff 255														
	static int					thissat = 255;                               // Starting hue.

	uint8_t secondHand = (millis() / 1000) % 15;							// Change '15' to a different value to change duration of the loop.
	static uint8_t lastSecond = 99;

	if (lastSecond != secondHand)
	{
		lastSecond = secondHand;
		switch (secondHand) {
		case  0: thissat = 50; break;
		case  5: thissat = 255; break;
		case 10: thissat = 255; break;
		case 15: thissat = 170; break;
		}
	}

	EVERY_N_MILLISECONDS(40)
	{
		fadeToBlackBy(leds, NUM_LEDS, beatsin8(5, LEDSettings.SpeedMultiplikator / 2, LEDSettings.SpeedMultiplikator * 2));
		int pos = random16(NUM_LEDS);									// Pick an LED at random.
		leds[pos] += CHSV(random16(huediff), thissat, 255);
	}

	LEDSettings.ChangesToEffectMade = 1;								//periodic update needed
}

//display a marching rainbow
void DisplayEffectRainbowMarch()
{                                       
	static uint16_t start = 0;  
	static uint16_t start2 = NUM_LEDS; // Hue change between pixels.

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(leds, NUM_LEDS, ExtractColorCHSV(start), ExtractColorCHSV(start2),FORWARD_HUES);            // Use FastLED's fill_rainbow routine.
		
		start= start + (LEDSettings.SpeedMultiplikator/2);
		if (start > 763)
			start = start-764;
		
		start2 = start2 + (LEDSettings.SpeedMultiplikator/2);
		if (start2 > 763)
			start2 = start2-764;
	}
	LEDSettings.ChangesToEffectMade = 1;	//periodic update needed
}

//display a Rainbow going back and forth using a sinus curve
void DisplayEffectRainbowBeat()
{
	static uint16_t start = 0;
	static uint16_t start2 = NUM_LEDS; // Hue change between pixels.

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(leds, NUM_LEDS, ExtractColorCHSV(start), ExtractColorCHSV(start2), FORWARD_HUES);            // Use FastLED's fill_rainbow routine.

		start = start + beatsin16(5,LEDSettings.SpeedMultiplikator/2,LEDSettings.SpeedMultiplikator*2);
		if (start > 763)
			start = start - 764;

		start2 = start2 + beatsin16(5, LEDSettings.SpeedMultiplikator / 2, LEDSettings.SpeedMultiplikator * 2);
		if (start2 > 763)
			start2 = start2 - 764;
	}
	LEDSettings.ChangesToEffectMade = 1;	//periodic update needed
}

//testing
void DisplayEffectColorPalBeat()
{
	EVERY_N_MILLISECONDS(400)
	{
		static CRGBPalette16 currentPalette;
		static TBlendType    currentBlending;
		currentPalette = PartyColors_p;
		currentBlending = LINEARBLEND;
		static uint8_t startIndex = 0;
		static uint8_t colorIndex = 0;
		startIndex = startIndex + 1; /* motion speed */
		for (int i = 0; i < NUM_LEDS; i++) {
			leds[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);

			colorIndex += 1;
		}
	}

}

//filling all the leds with the same color and fading between
void DisplayEffectFade()
{
	static uint16_t Counter = 0;
	EVERY_N_MILLISECONDS(2)
	{
		fill_solid(leds, NUM_LEDS, ExtractColor(Counter));
		Counter = Counter + (LEDSettings.SpeedMultiplikator-1);
		if (Counter > 764)
			Counter = Counter-764;
	}
	LEDSettings.ChangesToEffectMade = 1;
}

void DisplayEffectRGBFade()
{
	static int16_t Counter = 0;
	static uint8_t state = 0;
	CRGB temp;
	EVERY_N_MILLISECONDS(40)
	{
		
		switch (state)
		{
		case 0: 
			temp.setRGB(Counter, 0, 0);
			Counter = Counter + (LEDSettings.SpeedMultiplikator-1);
			break;
		case 1:
			temp.setRGB(Counter, 0, 0);
			Counter = Counter - (LEDSettings.SpeedMultiplikator - 1);
			break;
		case 2:
			temp.setRGB(0, Counter, 0);
			Counter = Counter + (LEDSettings.SpeedMultiplikator - 1);
			break;
		case 3:
			temp.setRGB(0, Counter, 0);
			Counter = Counter - (LEDSettings.SpeedMultiplikator - 1);
			break;
		case 4:
			temp.setRGB(0, 0, Counter);
			Counter = Counter + (LEDSettings.SpeedMultiplikator - 1);
			break;
		case 5:
			temp.setRGB(0, 0, Counter);
			Counter = Counter - (LEDSettings.SpeedMultiplikator - 1);
			break;
		}

		if (Counter > 255)
		{
			Counter = 255;
			++state;
		}
		if (Counter < 0)
		{
			Counter = 0;
			++state;
		}
		if (state >= 6)
			state = 0;

		fill_solid(leds, NUM_LEDS, temp);

	}
	LEDSettings.ChangesToEffectMade = 1;
}

//Display a fire effect
void DisplayEffectFire()
{
	leds[random16(NUM_LEDS)]= HeatColor(random8(255));

	LEDSettings.ChangesToEffectMade = 1;
}

void DisplayEffectStrobe()
{
	static uint8_t counter = 0;

	if (counter < 12)
	{
		if (counter == 0 || counter == 2 || counter == 4 || counter == 6 || counter == 8 || counter == 10 || counter == 12)
		{
			EVERY_N_MILLISECONDS(50)
			{
				fill_solid(leds, NUM_LEDS, CRGB::White);
				++counter;
			}
		}
		else
		{
			EVERY_N_MILLISECONDS(50)
			{
				fill_solid(leds, NUM_LEDS, CRGB::Black);
				++counter;
			}
		}
	}
	else
	{
		EVERY_N_MILLISECONDS(50)
		{
			counter=counter+random16(255);
			if (counter > 200)
				counter = 0;
			else
				counter = 15;
		}
	}
	

}

//Showing only the right side in white
void DisplayEffectNight()
{
	for (int dot = 0; dot <= NUM_LEDS; dot++)
	{
		if (dot%LEDSettings.SpeedMultiplikator)
			leds[dot] = CHSV(60, 128, 0);
		else
			leds[dot] = CHSV(255, 165, 255);
	}
	LEDSettings.ChangesToEffectMade = 0; //no periodically changes needed

}
