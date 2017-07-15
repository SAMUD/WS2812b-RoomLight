
void DisplayEffectMain()
{
	//DisplayMode has changed.
	if (Settings.DisplayMode != Settings.DisplayModeOld)
	{
		DisplayEffectTransition();							//show a transition from one to the other effect
		Settings.DisplayModeOld = Settings.DisplayMode;
		Settings.ChangesToEffectMade = 1;
	}

	//Select the right effect from the list
	if ((Settings.DisplayMode ==White || Settings.DisplayMode== White2) && Settings.ChangesToEffectMade)
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
	else if (Settings.DisplayMode == Ball && Settings.ChangesToEffectMade)
		DisplayEffectBall();
	else if (Settings.DisplayMode == AudioMeter && Settings.ChangesToEffectMade)
		DisplayEffectAudioMeter();
	

	
}

//Transition
void DisplayEffectTransition()
{
	//currently not used
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
	EVERY_N_MILLISECONDS(20)
	{
		uint8_t CurrentSpeed = Settings.Current.SpeedColor;

		if (CurrentSpeed < 10)
			CurrentSpeed = 10;

		/*uint8_t beatA = beatsin16(Settings.Current.SpeedColor/4, 0, 255);								// Starting hue
		uint8_t beatB = beatsin16(Settings.Current.SpeedColor/6, 0, 255);
		uint8_t beatC = beatsin16(Settings.Current.SpeedColor/10, 0, 255);
		fill_rainbow(ledstemp, NUM_LEDS, (beatA + beatB+ beatC) / 3, Settings.Current.Saturation/15);   // Use FastLED's fill_rainbow routine.*/
		//Simplified to:
		fill_rainbow(ledstemp, NUM_LEDS, (beatsin16(Settings.Current.SpeedColor / 4, 0, 255) +
										  beatsin16(Settings.Current.SpeedColor / 6, 0, 255) +
										  beatsin16(Settings.Current.SpeedColor / 10, 0, 255)) / 3, Settings.Current.Saturation / 15);   // Use FastLED's fill_rainbow routine.
	}
	
	Settings.ChangesToEffectMade = 1;	//periodic update needed

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

	/*static CRGBPalette16 currentPalette;

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
	}*/

	EVERY_N_MILLISECONDS(40)
	{
		uint8_t CurrentSpeed = Settings.Current.SpeedColor;
		static uint8_t ColorWheel = 0;

		if (CurrentSpeed < 6)
			CurrentSpeed = 6;

		EVERY_N_MILLISECONDS(1000)
		{
			if(Settings.PlayPause == true)
				ColorWheel = ColorWheel + beatsin8(CurrentSpeed / 10, 1, 10);
		}

		uint16_t inner = beatsin16(CurrentSpeed/6, NUM_LEDS / 4, NUM_LEDS / 4 * 3);    // Move 1/4 to 3/4
		uint16_t outer = beatsin16(CurrentSpeed / 6, 0, NUM_LEDS - 1);               // Move entire length
		uint16_t middle = beatsin16(CurrentSpeed / 6, NUM_LEDS / 3, NUM_LEDS / 3 * 2);   // Move 1/3 to 2/3

		ledstemp[middle] = CHSV(ColorWheel+40, Settings.Current.Saturation, 255);
		ledstemp[inner] = CHSV(ColorWheel+20, Settings.Current.Saturation, 255);
		ledstemp[outer] = CHSV(ColorWheel, Settings.Current.Saturation, 255);

		nscale8(ledstemp, NUM_LEDS, Settings.Current.Set+250);
	}
	
	Settings.ChangesToEffectMade = 1;
}

void DisplayEffectAudioMeter()
{
	uint16_t  i;
	static uint16_t minLvl, maxLvl;
	static uint16_t      n, height;

	n = analogRead(MIC_PIN);                                    // Raw reading from mic
	n = abs(n - DC_OFFSET);                               // Center on zero

	Serial.println(n);

	n = (n <= NOISE) ? 0 : (n - NOISE);                         // Remove noise/hum
	lvl = ((lvl * 7) + n) >> 3;                                 // "Dampened" reading (else looks twitchy)

																// Calculate bar height based on dynamic min/max levels (fixed point):
	height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);

	if (height < 0L)       height = 0;                          // Clip output
	else if (height > TOP) height = TOP;
	if (height > peak)     peak = height;                     // Keep 'peak' dot at top

															  // Color pixels based on rainbow gradient
	for (i = 0; i<NUM_LEDS; i++)
	{
		if (i >= height)   leds[i].setRGB(0, 0, 0);
		else ledstemp[i] = CHSV(map(i, 0, NUM_LEDS - 1, 30, 150), 255, 255);
	}

	// Draw peak dot  
	if (peak > 0 && peak <= NUM_LEDS - 1) ledstemp[peak] = CHSV(map(peak, 0, NUM_LEDS - 1, 30, 150), 255, 255);

	// Every few frames, make the peak pixel drop by 1:
	if (++dotCount >= PEAK_FALL) {                            // fall rate 
		if (peak > 0) peak--;
		dotCount = 0;
	}

	vol[volCount] = n;                                          // Save sample for dynamic leveling
	if (++volCount >= SAMPLES) volCount = 0;                    // Advance/rollover sample counter

														// Get volume range of prior frames
	minLvl = maxLvl = vol[0];
	for (i = 1; i<SAMPLES; i++) {
		if (vol[i] < minLvl)      minLvl = vol[i];
		else if (vol[i] > maxLvl) maxLvl = vol[i];
	}
	// minLvl and maxLvl indicate the volume range over prior frames, used
	// for vertically scaling the output graph (so it looks interesting
	// regardless of volume level).  If they're too close together though
	// (e.g. at very low volume levels) the graph becomes super coarse
	// and 'jumpy'...so keep some minimum distance between them (this
	// also lets the graph go to zero when no sound is playing):
	if ((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;
	minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6;                 // Dampen min/max levels
	maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6;                 // (fake rolling average)

	Settings.ChangesToEffectMade = 1;
}

