void DisplayEffectMain()
{
	if (LEDSettings.DisplayMode != LEDSettings.DisplayModeOld)
	{
		DisplayEffectTransition();
		LEDSettings.DisplayModeOld = LEDSettings.DisplayMode;
		LEDSettings.ChangesToEffectMade = 1;
	}

	if (LEDSettings.DisplayMode == WhiteAll && LEDSettings.ChangesToEffectMade)
		DisplayEffectWhiteAll();
	else if (LEDSettings.DisplayMode == WhiteLeft && LEDSettings.ChangesToEffectMade)
		DisplayEffectWhiteLeft();
	else if (LEDSettings.DisplayMode == WhiteRight && LEDSettings.ChangesToEffectMade)
		DisplayEffectWhiteRight();
	else if (LEDSettings.DisplayMode == Confetti && LEDSettings.ChangesToEffectMade)
		DisplayEffectConfetti();
	else if (LEDSettings.DisplayMode == RainbowMarch && LEDSettings.ChangesToEffectMade)
		DisplayEffectRainbowMarch();
	else if (LEDSettings.DisplayMode == RainbowBeat && LEDSettings.ChangesToEffectMade)
		DisplayEffectRainbowBeat();

	
}

void DisplayEffectTransition()
{

}

void DisplayEffectWhiteAll()
{
	Serial.println("EffectWhiteAll");
	for (int dot = 0; dot < NUM_LEDS; dot++)
	{
		leds[dot] = CHSV(LEDSettings.Hue+42, LEDSettings.Saturation,255);
		//show_at_max_brightness_for_power();
		//clear this led for the next time around the loop
		//leds[dot] = CHSV(50, 255, 50);
		//delay(5);
		LEDSettings.ChangesToEffectMade = 0;
		
	}
}

void DisplayEffectWhiteLeft()
{
	float temp;
	uint8_t temp2;
	Serial.println("EffectWhiteLeft");
	for (int dot = 0; dot < NUM_LEDS; dot++)
	{
		if (dot < NumberLEDLeft)
		{
			leds[dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation,255);
		}
		else if (dot < NumberLEDLeft + NumberLEDTransition)
		{
			temp = 100 / NumberLEDTransition; //decrementor in percentage of full value
			temp2 =((NumberLEDLeft+NumberLEDTransition) - dot);
			temp = 255 * ((temp2*temp)/100);
			if (temp < ValueLEDDarkside)
					temp = ValueLEDDarkside;
			
			leds[dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, temp2);
		}
		else
		{
			leds[dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, ValueLEDDarkside);
		}


	}

	LEDSettings.ChangesToEffectMade = 0;
}

void DisplayEffectWhiteRight()
{
	float temp3;
	uint8_t temp4;
	Serial.println("EffectWhiteRight");
	for (int dot = 1; dot <= NUM_LEDS; dot++)
	{
		if (dot < NUM_LEDS-(NumberLEDRight+NumberLEDTransition))
		{
			leds[NUM_LEDS - dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, ValueLEDDarkside);
		}
		else if (dot < NUM_LEDS-NumberLEDRight)
		{
			temp3 = 100 / NumberLEDTransition; //decrementor in percentage of full value
			temp4 = NUM_LEDS - (NumberLEDRight + NumberLEDTransition); //LEDS on the left side with dark value
			temp4 = (NumberLEDTransition+1) - ((temp4 + NumberLEDTransition) - dot);
			temp3 = 255 * ((temp4*temp3) / 100);
			if (temp3 < ValueLEDDarkside)
				temp3= ValueLEDDarkside;

			leds[NUM_LEDS-dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, temp3);
		}
		else
		{
			leds[NUM_LEDS - dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, 255);
		}


	}

	LEDSettings.ChangesToEffectMade = 0;

}

void DisplayEffectConfetti()
{
	uint8_t  thisfade = 5;                                        // How quickly does it fade? Lower = slower fade rate.
	int       thishue = 50;                                       // Starting hue.
	uint8_t   thisinc = 1;                                        // Incremental value for rotating hues
	uint8_t   thissat = 255;                                      // The saturation, where 255 = brilliant colours.
	uint8_t   thisbri = 255;                                      // Brightness of a sequence. Remember, max_bright is the overall limiter.
	int       huediff = 512;                                      // Range of random #'s to use for hue
	uint8_t thisdelay = 20;                                        // We don't need much delay (if any)

	uint8_t secondHand = (millis() / 1000) % 10;                // IMPORTANT!!! Change '15' to a different value to change duration of the loop.
	static uint8_t lastSecond = 99;                             // Static variable, means it's only defined once. This is our 'debounce' variable.
	if (lastSecond != secondHand) {                             // Debounce to make sure we're not repeating an assignment.
		lastSecond = secondHand;
		switch (secondHand) {
		case  0: thisinc = 1; thishue = 192; thissat = 255; thisfade = 2; huediff = 256; break;  // You can change values here, one at a time , or altogether.
		case  5: thisinc = 2; thishue = 128; thisfade = 8; huediff = 64; break;
		case 10: thisinc = 1; thishue = random16(255); thisfade = 1; huediff = 16; break;      // Only gets called once, and not continuously for the next several seconds. Therefore, no rainbows.
		case 15: break;                                                                // Here's the matching 15 for the other one.
		}
	}

	EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking delay to update/display the sequence.
		fadeToBlackBy(leds, NUM_LEDS, thisfade);                    // Low values = slower fade.
		int pos = random16(NUM_LEDS);                               // Pick an LED at random.
		leds[pos] += CHSV((thishue + random16(huediff)) / 4, thissat, thisbri);  // I use 12 bits for hue so that the hue increment isn't too quick.
		thishue = thishue + thisinc;
	}

	LEDSettings.ChangesToEffectMade = 1;
	
}

void DisplayEffectRainbowMarch()
{
	uint8_t thisdelay = 5;                                        // A delay value for the sequence(s)
	uint8_t thishue = 0;                                          // Starting hue value.
	uint8_t deltahue = 10;                                        // Hue change between pixels.

	thishue++;                                                  // Increment the starting hue.
	fill_rainbow(leds, NUM_LEDS, thishue, deltahue);            // Use FastLED's fill_rainbow routine.

	LEDSettings.ChangesToEffectMade = 1;
}

void DisplayEffectRainbowBeat()
{
	uint8_t beatA = beatsin8(5, 0, 255);                        // Starting hue
	uint8_t beatB = beatsin8(15, 4, 20);                        // Delta hue between LED's
	fill_rainbow(leds, NUM_LEDS, beatA, beatB);                 // Use FastLED's fill_rainbow routine.

	LEDSettings.ChangesToEffectMade = 1;
}