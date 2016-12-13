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


//index can be a value from 0 to 765
//function will then extract an appropriate value around all the possible values
CRGB ExtractColor(uint16_t index)
{
	CRGB temp;

	while (index > 764)
		//index is to big. trimming index
		index = index - 764;


	if (index < 256)
	{
		//first Part of extracting. 
		//index=0 --> 255 0 0 index=255 --> 0 255 0
		temp.r = 255 - index;
		temp.g = index;
		temp.b = 0;
	}
	else if (index < 511)
	{
		//second part
		//trim index
		index = index - 255;
		//index=0 --> 0 254 1 index=255 --> 0 0 255
		temp.r = 0;
		temp.g = 255 - index;
		temp.b = index;
	}
	else
	{
		//third part
		//trim index
		index = index - 510;
		//index=0 --> 1 0 254 index=254 --> 254 0 1
		temp.r = index;
		temp.g = 0;
		temp.b = 255-index;
	}

	return temp;
}

CHSV ExtractColorCHSV(uint16_t index)
{
	static bool initdone = false;
	static CHSV Palette[764];

	if (!initdone)
	{
		//do init
		initdone = true;
		fill_gradient(Palette, 0, CHSV(100, 255, 255),763, CHSV(99, 255, 255), FORWARD_HUES);
	}

	if (index > 764)
		index = index - 764;

	return Palette[index];
}