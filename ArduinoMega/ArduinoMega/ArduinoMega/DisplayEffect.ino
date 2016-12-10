

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
	else if (LEDSettings.DisplayMode == ConfettiColorfull && LEDSettings.ChangesToEffectMade && LEDSettings.PlayPause)
		DisplayEffectConfettiColorfull();

	
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
	static uint8_t		thisfade = 0;								// How quickly does it fade? Lower = slower fade rate.
	static int			thishue = 0;                                // Starting hue.
	static int8_t				thisinc = 3;                               // Incremental value for rotating hues
	static int					huediff = 1024;                              // Range of random #'s to use for hue
	uint8_t secondHand = (millis() / 1000) % 15;					// IMPORTANT!!! Change '15' to a different value to change duration of the loop.
	static uint8_t lastSecond = 99;									// Static variable, means it's only defined once. This is our 'debounce' variable.
	
	if (lastSecond != secondHand) 
	{							
		lastSecond = secondHand;
		switch (secondHand) {
		case  0: thisinc = 0; thisfade = LEDSettings.SpeedMultiplikator;		huediff = 0; break;  // You can change values here, one at a time , or altogether.
		case  5: thisinc = 2; thisfade = LEDSettings.SpeedMultiplikator;		huediff = 100; break;
		case 10: thisinc = 1; thisfade = LEDSettings.SpeedMultiplikator/2;	huediff = 100; break;      // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
		case 15: thisinc = 1; thisfade = LEDSettings.SpeedMultiplikator / 2;	huediff = 30;;																		// Here's the matching 15 for the other one.
		}
	}

	EVERY_N_MILLISECONDS(40) 
	{								// FastLED based non-blocking delay to update/display the sequence.
		fadeToBlackBy(leds, NUM_LEDS, thisfade);                    // Low values = slower fade.
		int pos = random16(NUM_LEDS);                               // Pick an LED at random.
		leds[pos] += CHSV((thishue+random16(huediff))/4, 255, 255);  // I use 12 bits for hue so that the hue increment isn't too quick.
		thishue = thishue + thisinc;
	}

	LEDSettings.ChangesToEffectMade = 1; //periodic update needed
}

void DisplayEffectConfettiColorfull()
{
	static uint8_t		thisfade = LEDSettings.SpeedMultiplikator;        // How quickly does it fade? Lower = slower fade rate.
	static int			thishue = 0;                                       // Starting hue.
	static uint8_t		thissat = 255;                                      // The saturation, where 255 = brilliant colours. 
	uint8_t secondHand = (millis() / 1000) % 15;					// IMPORTANT!!! Change '15' to a different value to change duration of the loop.
	static uint8_t lastSecond = 99;									// Static variable, means it's only defined once. This is our 'debounce' variable.

	if (lastSecond != secondHand)
	{
		lastSecond = secondHand;
		switch (secondHand) {
		case  0: thishue = 0;				thissat = 0;	thisfade = LEDSettings.SpeedMultiplikator/3; break;  // You can change values here, one at a time , or altogether.
		case  5: thishue = random16(255);	thissat = 255;	thisfade = LEDSettings.SpeedMultiplikator; ; break;
		case 10: thishue = random16(255);	thissat = 255;	thisfade = LEDSettings.SpeedMultiplikator/2; break;      // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
		case 15: thishue = random16(255);	thissat = 255;	thisfade = LEDSettings.SpeedMultiplikator; break;																		// Here's the matching 15 for the other one.
		}
	}

	EVERY_N_MILLISECONDS(40)
	{																// FastLED based non-blocking delay to update/display the sequence.
		fadeToBlackBy(leds, NUM_LEDS, thisfade);                    // Low values = slower fade.
		int pos = random16(NUM_LEDS);                               // Pick an LED at random.
		leds[pos] += CHSV(random16(255), thissat, 255);  
	}

	LEDSettings.ChangesToEffectMade = 1; //periodic update needed
}

//display a marching rainbow
void DisplayEffectRainbowMarch()
{                                       
	static uint16_t start = 0;  
	static uint16_t start2 = 500; // Hue change between pixels.

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(leds, NUM_LEDS, ExtractColorCHSV(start), ExtractColorCHSV(start2),FORWARD_HUES);            // Use FastLED's fill_rainbow routine.
		
		start= start + (LEDSettings.SpeedMultiplikator/2);
		if (start > 1023)
			start = start-1023;
		
		start2 = start2 + (LEDSettings.SpeedMultiplikator/2);
		if (start2 > 1023)
			start2 = start2-1023;
	}
	LEDSettings.ChangesToEffectMade = 1;	//periodic update needed
}

//display a Rainbow going back and forth using a sinus curve
void DisplayEffectRainbowBeat()
{
	static uint16_t start = 0;
	static uint16_t start2 = 500; // Hue change between pixels.

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(leds, NUM_LEDS, ExtractColorCHSV(start), ExtractColorCHSV(start2), FORWARD_HUES);            // Use FastLED's fill_rainbow routine.

		start = start + beatsin16(5,LEDSettings.SpeedMultiplikator/2,LEDSettings.SpeedMultiplikator*2);
		if (start > 1023)
			start = start - 1023;

		start2 = start2 + beatsin16(5, LEDSettings.SpeedMultiplikator / 2, LEDSettings.SpeedMultiplikator * 2);
		if (start2 > 1023)
			start2 = start2 - 1023;
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
	EVERY_N_MILLISECONDS(40)
	{
		fill_solid(leds, NUM_LEDS, ExtractColorCHSV(Counter));
		Counter = Counter + (LEDSettings.SpeedMultiplikator/2);
		if (Counter > 1023)
			Counter = Counter-1024;
	}
	LEDSettings.ChangesToEffectMade = 1;
}

//Display a fire effect
void DisplayEffectFire()
{
	CRGB HeatColor(uint8_t temperature);
}
