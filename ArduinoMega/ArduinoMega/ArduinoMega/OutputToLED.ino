void OutputToLEDMain()
{
	memmove(&leds[0], &ledstemp[0], NUM_LEDS * sizeof(CRGB));
	OutputToLEDDisplayMode(); //crop the LED-Output
	OutputToLEDDisplayInfo(); //show button pressed info

	FastLED.show();
}

void OutputToLEDDisplayMode()
{
	static uint16_t dot = 0;
	if (Settings.Current.DisplayMode == Left)
	{
		fill_solid(&leds[NumberLEDLeft], NUM_LEDS-NumberLEDLeft, CHSV(0, 0, 0));
	}
	if (Settings.Current.DisplayMode == Right)
	{
		fill_solid(leds, NUM_LEDS - (NumberLEDRight-1), CHSV(0, 0, 0));
	}
	if (Settings.Current.DisplayMode == Night)
	{
	
		for (dot = 0; dot < NUM_LEDS; dot=dot+1)
		{
			if (dot%Settings.Current.NightNumber)
				leds[dot] = CRGB::Black;
		}
	}
}

void OutputToLEDDisplayInfo()
{
	static uint8_t counter = 0;
	
	//if the state of the variable to show infos on the LEDs went true
	if (DisplayInfo.ShowACK)
	{
		counter = 25;
		DisplayInfo.ShowACK = 0;
#if defined (DEBUGMODE)
		Serial.println("OutputToLED | DisplayInfo updated ");
#endif // DEBUG


	}

	if (counter > 0)
	{
		//display info
		if (DisplayInfo.ShowPercentage > 0)
		{
			fill_solid(leds, DisplayInfo.ShowPercentage / 10, CRGB::Green);
			leds[25] = CRGB::Red;
		}
		else
		{
			leds[1] = CRGB::Green;
			leds[2] = CRGB::Red;
		}
		leds[0] = CRGB::Red;

		//decrease the counter
		EVERY_N_MILLISECONDS(100)
		{
			counter = counter - 1;
			if (counter == 0)
			{
				DisplayInfo.ShowPercentage = 0;
			}
		}

	}
}
