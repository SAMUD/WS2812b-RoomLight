void BlinkLed(uint16_t LEDdelay, uint16_t LEDTimeOn)
{
	static unsigned long millistemp;
	static bool state;
	if ((millis() - millistemp > LEDdelay) && state==0)
	{
		millistemp = millis();
		state = !state;
		digitalWrite(13, state);

	}
	if ((millis() - millistemp > LEDTimeOn) && state == 1)
	{
		millistemp = millis();
		state = !state;
		digitalWrite(13, state);
	}
}

/*CRGB ExtractColor(uint16_t index)
{
	static bool initdone = false;
	uint8_t paletteCounter = 1;

	static CRGBPalette256 firstPalette;
	static CRGBPalette256 secondPalette;
	static CRGBPalette256 thirdPalette;
	static CRGBPalette256 fourPalette;
	static CRGBPalette256 fivePalette;

	if (!initdone)
	{
		//do init
		initdone = true;

		CHSV one;
		CHSV two;

		fill_gradient_RGB(firstPalette, 256, CHSV(0, 255, 255), CHSV(50, 255, 255));
		fill_gradient_RGB(secondPalette, 256, CHSV(51, 255, 255), CHSV(101, 255, 255));
		fill_gradient_RGB(thirdPalette, 256, CHSV(102, 255, 255), CHSV(152, 255, 255));
		//fill_gradient_RGB(firstPalette, 255, CHSV(0, 255, 255), CHSV(50, 255, 255), SHORTEST_HUES);
		//fill_gradient_RGB(secondPalette, 255, CHSV(51, 255, 255), CHSV(101, 255, 255), SHORTEST_HUES);
		//fill_gradient_RGB(thirdPalette, 255, CHSV(102, 255, 255), CHSV(152, 255, 255), SHORTEST_HUES);
		fill_gradient_RGB(fourPalette, 256, CHSV(153, 255, 255), CHSV(203, 255, 255));
		fill_gradient_RGB(fivePalette, 256, CHSV(204, 255, 255), CHSV(255, 255, 255));
	}

	if (index > (256 * 5))
		index = index - (256 * 5);

	paletteCounter = 1;
	while (index > 255)
	{
		++paletteCounter;
		index = index - 255;
	}

	switch (paletteCounter)
	{
	case 1: 
		//Serial.print("from 1   ");
		return ColorFromPalette(firstPalette, index, 255);
	case 2: 
		//Serial.print("from 2   ");
		return ColorFromPalette(secondPalette, index, 255);
	case 3: 
		//Serial.print("from 3   ");
		return ColorFromPalette(thirdPalette, index, 255);
	case 4: 
		//Serial.print("from 4   ");
		return ColorFromPalette(fourPalette, index, 255);
	case 5: 
		//Serial.print("from 5   ");
		return ColorFromPalette(fivePalette, index, 255);
	}
}*/

CHSV ExtractColorCHSV(uint16_t index)
{
	static bool initdone = false;
	static CHSV Palette[1024];

	if (!initdone)
	{
		//do init
		initdone = true;
		fill_gradient(Palette, 0, CHSV(100, 255, 255),1023, CHSV(99, 255, 255), FORWARD_HUES);
	}

	if (index > 1023)
		index = index - 1023;

	return Palette[index];
}