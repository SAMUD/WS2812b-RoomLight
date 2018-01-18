
void DisplayEffectMain()
{
	//DisplayMode has changed.
	if (Settings.EffectNumber != Settings.EffectNumberOld)
	{
		DisplayEffectTransition();							//show a transition from one to the other effect
		Settings.EffectNumberOld = Settings.EffectNumber;
		SettingsNow.ChangesToEffectMade = true;
	}

	//Select the right effect from the list
	if (Settings.EffectNumber <= White2 && SettingsNow.ChangesToEffectMade)
		DisplayEffectWhite();
	else if (Settings.EffectNumber <= FixedColor3 && SettingsNow.ChangesToEffectMade )
		DisplayEffectFixedColor();
	else if (Settings.EffectNumber <= Confetti1 && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectConfettiColorfull();
	else if (Settings.EffectNumber == RainbowMarch && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectRainbowMarch();
	else if (Settings.EffectNumber == RainbowBeat && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectRainbowBeat();
	else if (Settings.EffectNumber == ColorPalBeat && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectColorPalBeat();
	else if (Settings.EffectNumber == Fade && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectFade();
	else if (Settings.EffectNumber == RGBFade && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectRGBFade();
	else if (Settings.EffectNumber == Strobe && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectStrobe();
	else if (Settings.EffectNumber == Ball && SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
		DisplayEffectBall();
	else if (Settings.EffectNumber == TotalWhite && SettingsNow.ChangesToEffectMade)
		DisplayEffectWhite();
	else if (SettingsNow.ChangesToEffectMade && SettingsNow.PlayPause)
	{
#ifdef DEBUGMODE
		Serial.print("DisplyEffect: Error. EffectNumber: ");
		Serial.println(Settings.EffectNumber);
#endif // DEBUGMODE		
	}	
}

//Transition
void DisplayEffectTransition()
{
	//currently not used
}

//Showing all LEDs in white
void DisplayEffectWhite()
{
	fill_solid(ledstemp, NUM_LEDS, Settings.LedEffects[Settings.EffectNumber].Temperature);
	SettingsNow.ChangesToEffectMade = false;
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
		fadeToBlackBy(ledstemp, NUM_LEDS, beatsin8(5, Settings.LedEffects[Settings.EffectNumber].Speed / 2, Settings.LedEffects[Settings.EffectNumber].Speed * 2));
		int pos = random16(NUM_LEDS);									// Pick an LED at random.
		ledstemp[pos] += CHSV(random16(huediff), thissat, 255);
	}

	SettingsNow.ChangesToEffectMade = true;								//periodic update needed
}

//display a marching rainbow
void DisplayEffectRainbowMarch()
{                                       
	static uint8_t start = 0;  
	static uint8_t start2 = 150; // Hue change between pixels.
	static uint8_t counter;

	EVERY_N_MILLISECONDS(40)
	{

		fill_gradient(ledstemp, NUM_LEDS, CHSV(start, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), CHSV(start2, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), FORWARD_HUES);
		
		if (Settings.LedEffects[Settings.EffectNumber].Speed>128)
		{
			start = start + (((Settings.LedEffects[Settings.EffectNumber].Speed-128) / 10) + 1);
			start2 = start2 + (((Settings.LedEffects[Settings.EffectNumber].Speed-128) / 10) + 1);
		}
		else
		{
			if (counter < Settings.LedEffects[Settings.EffectNumber].Speed)
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
	SettingsNow.ChangesToEffectMade = true;	//periodic update needed
}

//display a Rainbow going back and forth using a sinus curve
void DisplayEffectRainbowBeat()
{
	static uint8_t start = 0;
	static uint8_t start2 = 150; // Hue change between pixels.
	static uint8_t counter = 0;

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(ledstemp, NUM_LEDS, CHSV(start, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), CHSV(start2, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), FORWARD_HUES);

		if (Settings.LedEffects[Settings.EffectNumber].Speed>128)
		{
			start = start + beatsin16(5, (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1), (((Settings.LedEffects[Settings.EffectNumber].Speed - 75) / 10) + 1)); 
			start2 = start2 + beatsin16(5, (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1), (((Settings.LedEffects[Settings.EffectNumber].Speed - 75) / 10) + 1));
		}
		else
		{
			if (counter < Settings.LedEffects[Settings.EffectNumber].Speed)
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
	SettingsNow.ChangesToEffectMade = true;	//periodic update needed
}

//testing
void DisplayEffectColorPalBeat()
{
	EVERY_N_MILLISECONDS(20)
	{
		uint8_t CurrentSpeed = Settings.LedEffects[Settings.EffectNumber].Speed;

		if (CurrentSpeed < 10)
			CurrentSpeed = 10;

		/*uint8_t beatA = beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed/4, 0, 255);								// Starting hue
		uint8_t beatB = beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed/6, 0, 255);
		uint8_t beatC = beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed/10, 0, 255);
		fill_rainbow(ledstemp, NUM_LEDS, (beatA + beatB+ beatC) / 3, Settings.LedEffects[Settings.EffectNumber].Saturation/15);   // Use FastLED's fill_rainbow routine.*/
		//Simplified to:
		fill_rainbow(ledstemp, NUM_LEDS, (beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed / 4, 0, 255) +
										  beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed / 6, 0, 255) +
										  beatsin16(Settings.LedEffects[Settings.EffectNumber].Speed / 10, 0, 255)) / 3, Settings.LedEffects[Settings.EffectNumber].Saturation / 15);   // Use FastLED's fill_rainbow routine.
	}
	
	SettingsNow.ChangesToEffectMade = true;	//periodic update needed

}

//filling all the leds with the same color and fading between
void DisplayEffectFade()
{
	static uint8_t counter = 128;
	static uint8_t start = 0;
	static uint8_t start2 = 15; // Hue change between pixels.

	EVERY_N_MILLISECONDS(40)
	{
		fill_gradient(ledstemp, NUM_LEDS, CHSV(start, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), CHSV(start2, Settings.LedEffects[Settings.EffectNumber].Saturation, 255), FORWARD_HUES);

		if (Settings.LedEffects[Settings.EffectNumber].Speed>128)
		{
			start = start + (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1);
			start2 = start2 + (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1);
		}
		else
		{
			if (counter < Settings.LedEffects[Settings.EffectNumber].Speed)
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
	SettingsNow.ChangesToEffectMade = true;
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
		
		if (Settings.LedEffects[Settings.EffectNumber].Speed>128)
			start = start + (((Settings.LedEffects[Settings.EffectNumber].Speed - 128) / 10) + 1);
		else
		{
			if (counter < Settings.LedEffects[Settings.EffectNumber].Speed)
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
	SettingsNow.ChangesToEffectMade = true;
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
	fill_solid(ledstemp, NUM_LEDS, CHSV(Settings.LedEffects[Settings.EffectNumber].Speed,Settings.LedEffects[Settings.EffectNumber].Saturation,255));
	Serial.print("Color and Saturation:");
	Serial.print(Settings.LedEffects[Settings.EffectNumber].Speed);
	Serial.print("  ");
	Serial.println(Settings.LedEffects[Settings.EffectNumber].Saturation);
	SettingsNow.ChangesToEffectMade = false;
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
		uint8_t CurrentSpeed = Settings.LedEffects[Settings.EffectNumber].Speed;
		static uint8_t ColorWheel = 0;

		if (CurrentSpeed < 6)
			CurrentSpeed = 6;

		EVERY_N_MILLISECONDS(1000)
		{
			if(SettingsNow.PlayPause == true)
				ColorWheel = ColorWheel + beatsin8(CurrentSpeed / 10, 1, 10);
		}

		uint16_t inner = beatsin16(CurrentSpeed/6, NUM_LEDS / 4, NUM_LEDS / 4 * 3);    // Move 1/4 to 3/4
		uint16_t outer = beatsin16(CurrentSpeed / 6, 0, NUM_LEDS - 1);               // Move entire length
		uint16_t middle = beatsin16(CurrentSpeed / 6, NUM_LEDS / 3, NUM_LEDS / 3 * 2);   // Move 1/3 to 2/3

		ledstemp[middle] = CHSV(ColorWheel+40, Settings.LedEffects[Settings.EffectNumber].Saturation, 255);
		ledstemp[inner] = CHSV(ColorWheel+20, Settings.LedEffects[Settings.EffectNumber].Saturation, 255);
		ledstemp[outer] = CHSV(ColorWheel, Settings.LedEffects[Settings.EffectNumber].Saturation, 255);

		nscale8(ledstemp, NUM_LEDS, Settings.LedEffects[Settings.EffectNumber].Set+250);
	}
	
	SettingsNow.ChangesToEffectMade = true;
}



