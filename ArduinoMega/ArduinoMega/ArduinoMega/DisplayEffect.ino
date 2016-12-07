

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
	else if (LEDSettings.DisplayMode == Confetti && LEDSettings.ChangesToEffectMade  && LEDSettings.PlayPause)
		DisplayEffectConfetti();
	else if (LEDSettings.DisplayMode == RainbowMarch && LEDSettings.ChangesToEffectMade  && LEDSettings.PlayPause)
		DisplayEffectRainbowMarch();
	else if (LEDSettings.DisplayMode == RainbowBeat && LEDSettings.ChangesToEffectMade  && LEDSettings.PlayPause)
		DisplayEffectRainbowBeat();
	else if (LEDSettings.DisplayMode == ColorPalBeat && LEDSettings.ChangesToEffectMade && LEDSettings.PlayPause)
		DisplayEffectColorPalBeat();

	
}

void DisplayEffectTransition()
{

}

void DisplayEffectWhiteAll()
{
	Serial.println("EffectWhiteAll");
	fill_solid(leds, NUM_LEDS, LEDSettings.Temperature);
	LEDSettings.ChangesToEffectMade = 0;
}

void DisplayEffectWhiteLeft()
{
	float temp;
	uint8_t temp2;
	Serial.println("EffectWhiteLeft");

	fill_solid(leds, NUM_LEDS, CHSV(0, 0, ValueLEDDarkside));
	fill_solid(leds, NumberLEDLeft, LEDSettings.Temperature);
	

	LEDSettings.ChangesToEffectMade = 0;
}

void DisplayEffectWhiteRight()
{
	Serial.println("EffectWhiteRight");
	for (int dot = 1; dot <= NUM_LEDS; dot++)
	{
		if (dot < NumberLEDRight)
		{
			leds[NUM_LEDS - dot] = LEDSettings.Temperature;
		}
		else
		{
			leds[NUM_LEDS - dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, ValueLEDDarkside);
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
	static uint8_t thishue = 0;                                          // Starting hue value.
	uint8_t deltahue = 2;                                        // Hue change between pixels.

	EVERY_N_MILLISECONDS(30)
	{
		thishue++;                                                  // Increment the starting hue.
		fill_rainbow(leds, NUM_LEDS, thishue, deltahue);            // Use FastLED's fill_rainbow routine.

		LEDSettings.ChangesToEffectMade = 1;
	}

	
}

void DisplayEffectRainbowBeat()
{
	//EVERY_N_MILLISECONDS(20)
	{
		static uint8_t beatA;
		static uint8_t beatB;
		
		beatA = beatsin8(6, 0, 255);                        // Starting hue
		beatB = 1;                      // Delta hue between LED's
		fill_rainbow(leds, NUM_LEDS, beatA, beatB);                 // Use FastLED's fill_rainbow routine.

		LEDSettings.ChangesToEffectMade = 1;
	}
	
}

void DisplayEffectColorPalBeat()
{
	static CRGBPalette16 currentPalette;
	static CRGBPalette16 targetPalette;
	uint8_t maxChanges = 24;
	static TBlendType    currentBlending;

	currentPalette = RainbowColors_p;                           // RainbowColors_p; CloudColors_p; PartyColors_p; LavaColors_p; HeatColors_p;
	targetPalette = RainbowColors_p;                           // RainbowColors_p; CloudColors_p; PartyColors_p; LavaColors_p; HeatColors_p;
	currentBlending = LINEARBLEND;

	static uint8_t beatA = beatsin8(1, 0, 255);                        // Starting hue
	static uint8_t beatB = beatsin8(2, 2, 7);                       // Delta hue between LED's
	for (int i = 0; i < NUM_LEDS; i++) {
		leds[i] = ColorFromPalette(currentPalette, beatA, 255, currentBlending);
		beatA += beatB;
	}                         // Power managed display.

	EVERY_N_MILLISECONDS(100) {                                // FastLED based timer to update/display the sequence every 5 seconds.
		nblendPaletteTowardPalette(currentPalette, targetPalette, maxChanges);
	}

	EVERY_N_MILLISECONDS(5000) {                                // FastLED based timer to update/display the sequence every 5 seconds.
		targetPalette = CRGBPalette16(CHSV(random8(), 255, 32), CHSV(random8(), random8(64) + 192, 255), CHSV(random8(), 255, 32), CHSV(random8(), 255, 255));
	}

}