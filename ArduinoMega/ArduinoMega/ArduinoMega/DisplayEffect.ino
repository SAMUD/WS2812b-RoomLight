
void DisplayEffectMain()
{
	if (Settings.DisplayMode != Settings.DisplayModeOld)
	{
		DisplayEffectTransition();
		Settings.DisplayModeOld = Settings.DisplayMode;
		Settings.ChangesToEffectMade = 1;
	}

	//Select the right effect from the list
	if (Settings.DisplayMode == (White || White2) && Settings.ChangesToEffectMade)
		DisplayEffectWhite();
	else if (Settings.DisplayMode == Confetti && Settings.ChangesToEffectMade  && Settings.PlayPause)
		DisplayEffectConfetti();
	else if (Settings.DisplayMode == RainbowMarch && Settings.ChangesToEffectMade  && Settings.PlayPause)
		DisplayEffectRainbowMarch();
	else if (Settings.DisplayMode == RainbowBeat && Settings.ChangesToEffectMade  && Settings.PlayPause)
		DisplayEffectRainbowBeat();
	else if (Settings.DisplayMode == ColorPalBeat && Settings.ChangesToEffectMade && Settings.PlayPause)
		DisplayEffectColorPalBeat();
	else if (Settings.DisplayMode == Fade && Settings.ChangesToEffectMade && Settings.PlayPause)
		DisplayEffectFade();
	else if (Settings.DisplayMode == RGBFade && Settings.ChangesToEffectMade && Settings.PlayPause)
		DisplayEffectRGBFade();
	else if (Settings.DisplayMode == ConfettiColorfull && Settings.ChangesToEffectMade && Settings.PlayPause)
		DisplayEffectConfettiColorfull();
	else if (Settings.DisplayMode == Strobe && Settings.ChangesToEffectMade && Settings.PlayPause)
		DisplayEffectStrobe();
	else if ((Settings.DisplayMode == FixedColor || Settings.DisplayMode == FixedColor2 || Settings.DisplayMode == FixedColor3) && Settings.ChangesToEffectMade)
		DisplayEffectFixedColor();
	else if (Settings.DisplayMode == Ball && Settings.ChangesToEffectMade && Settings.PlayPause)
		DisplayEffectBall();
	

	
}

//Transition
void DisplayEffectTransition()
{

}

//Showing all LEDs in white
void DisplayEffectWhite()
{
	fill_solid(ledstemp, NUM_LEDS, Settings.Current.Temperature);
	Settings.ChangesToEffectMade = 0;
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
		fadeToBlackBy(ledstemp, NUM_LEDS, beatsin8(5,Settings.Current.SpeedColor/2,Settings.Current.SpeedColor*2));         
		int pos = random16(NUM_LEDS);									// Pick an LED at random.
		ledstemp[pos] += CHSV((thishue+random16(huediff))/4, 255, 255);		
		thishue = thishue + thisinc;
	}

	Settings.ChangesToEffectMade = 1; //periodic update needed
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
		fadeToBlackBy(ledstemp, NUM_LEDS, beatsin8(5, Settings.Current.SpeedColor / 2, Settings.Current.SpeedColor * 2));
		int pos = random16(NUM_LEDS);									// Pick an LED at random.
		ledstemp[pos] += CHSV(random16(huediff), thissat, 255);
	}

	Settings.ChangesToEffectMade = 1;								//periodic update needed
}

//display a marching rainbow
void DisplayEffectRainbowMarch()
{                                       
	static uint8_t start = 0;  
	static uint8_t start2 = 150; // Hue change between pixels.
	static uint8_t counter;

	EVERY_N_MILLISECONDS(40)
	{

		fill_gradient(ledstemp, NUM_LEDS, CHSV(start, Settings.Current.Saturation, 255), CHSV(start2, Settings.Current.Saturation, 255), FORWARD_HUES);
		
		if (Settings.Current.SpeedColor>128)
		{
			start = start + (((Settings.Current.SpeedColor-128) / 10) + 1);
			start2 = start2 + (((Settings.Current.SpeedColor-128) / 10) + 1);
		}
		else
		{
			if (counter < Settings.Current.SpeedColor)
			{
				counter = 129;
				++start;
				++start2;
			}
			--counter;
		}
		
		if (start > 255)
			start = start-255;
		if (start2 > 255)
			start2 = start2-255;
	}
	Settings.ChangesToEffectMade = 1;	//periodic update needed
}

//display a Rainbow going back and forth using a sinus curve
void DisplayEffectRainbowBeat()
{
	static uint8_t start = 0;
	static uint8_t start2 = 150; // Hue change between pixels.
	static uint8_t counter = 0;

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(ledstemp, NUM_LEDS, CHSV(start, Settings.Current.Saturation, 255), CHSV(start2, Settings.Current.Saturation, 255), FORWARD_HUES);

		if (Settings.Current.SpeedColor>128)
		{
			start = start + beatsin16(5, (((Settings.Current.SpeedColor - 128) / 10) + 1), (((Settings.Current.SpeedColor - 75) / 10) + 1)); 
			start2 = start2 + beatsin16(5, (((Settings.Current.SpeedColor - 128) / 10) + 1), (((Settings.Current.SpeedColor - 75) / 10) + 1));
		}
		else
		{
			if (counter < Settings.Current.SpeedColor)
			{
				counter = 129;
				start=start+ beatsin16(3, 1, 4);
				start2 = start2 + beatsin16(3, 1, 4);
			}
			--counter;
		}

		if (start > 255)
			start = start - 255;
		if (start2 > 255)
			start2 = start2 - 255;
	}
	Settings.ChangesToEffectMade = 1;	//periodic update needed
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
			ledstemp[i] = ColorFromPalette(currentPalette, colorIndex, 255, currentBlending);

			colorIndex += 1;
		}
	}

}

//filling all the leds with the same color and fading between
void DisplayEffectFade()
{
	static uint8_t counter = 128;
	static uint8_t start = 0;
	static uint8_t start2 = 15; // Hue change between pixels.

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(ledstemp, NUM_LEDS, CHSV(start, Settings.Current.Saturation, 255), CHSV(start2, Settings.Current.Saturation, 255), FORWARD_HUES);

		if (Settings.Current.SpeedColor>128)
		{
			start = start + (((Settings.Current.SpeedColor - 128) / 10) + 1);
			start2 = start2 + (((Settings.Current.SpeedColor - 128) / 10) + 1);
		}
		else
		{
			if (counter < Settings.Current.SpeedColor)
			{
				counter = 129;
				++start;
				++start2;
			}
			--counter;
		}

		if (start > 255)
			start = start - 255;
		if (start2 > 255)
			start2 = start2 - 255;
	}
	Settings.ChangesToEffectMade = 1;
}

void DisplayEffectRGBFade()
{
	static int16_t Counter = 0;
	static uint8_t counter = 128;
	static uint8_t start;
	static uint8_t state = 0;
	CRGB temp;
	EVERY_N_MILLISECONDS(40)
	{
		
		if (Settings.Current.SpeedColor>128)
			start = start + (((Settings.Current.SpeedColor - 128) / 10) + 1);
		else
		{
			if (counter < Settings.Current.SpeedColor)
			{
				counter = 129;
				++start;
			}
			--counter;
		}
		
		switch (state)
		{
		case 0: 
			temp.setRGB(Counter, 0, 0);
			Counter = Counter + start;
			break;
		case 1:
			temp.setRGB(Counter, 0, 0);
			Counter = Counter - start;
			break;
		case 2:
			temp.setRGB(0, Counter, 0);
			Counter = Counter + start;
			break;
		case 3:
			temp.setRGB(0, Counter, 0);
			Counter = Counter - start;
			break;
		case 4:
			temp.setRGB(0, 0, Counter);
			Counter = Counter + start;
			break;
		case 5:
			temp.setRGB(0, 0, Counter);
			Counter = Counter -start;
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

		fill_solid(ledstemp, NUM_LEDS, temp);

	}
	Settings.ChangesToEffectMade = 1;
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
				fill_solid(ledstemp, NUM_LEDS, CRGB::White);
				++counter;
			}
		}
		else
		{
			EVERY_N_MILLISECONDS(50)
			{
				fill_solid(ledstemp, NUM_LEDS, CRGB::Black);
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

void DisplayEffectFixedColor()
{
	fill_solid(ledstemp, NUM_LEDS, CHSV(Settings.Current.SpeedColor,Settings.Current.Saturation,255));
	Serial.print("Color and Saturation:");
	Serial.print(Settings.Current.SpeedColor);
	Serial.print("  ");
	Serial.println(Settings.Current.Saturation);
	Settings.ChangesToEffectMade = 0;
}

void DisplayEffectBall()
{

	static CRGBPalette16 currentPalette;

	static uint32_t xscale = 5;                                          // How far apart they are
	static uint32_t yscale = 1;                                           // How fast they move
	static uint8_t index = 0;

	currentPalette = CRGBPalette16(
		CRGB::Black, CRGB::Black, CRGB::Black, CHSV(0, 255, 4),
		CHSV(0, 255, 8), CRGB::Red, CRGB::Red, CRGB::Red,
		CRGB::DarkOrange, CRGB::Orange, CRGB::Orange, CRGB::Orange,
		CRGB::Yellow, CRGB::Yellow, CRGB::Gray, CRGB::Gray);

	EVERY_N_MILLISECONDS(40)
	{
		for (int i = 0; i < NUM_LEDS; i++) {
			index = inoise8(i*xscale, millis()*yscale*NUM_LEDS / 255);                                           // X location is constant, but we move along the Y at the rate of millis()
			ledstemp[i] = ColorFromPalette(currentPalette, min(i*(index) >> 6, 255), i * 255 / NUM_LEDS, LINEARBLEND);  // With that value, look up the 8 bit colour palette value and assign it to the current LED.
		}
	}
	
	Settings.ChangesToEffectMade = 1;
}