//show the LEDs after adding status infos and cropping the Output to the desired size
void OutputToLEDMain()
{
	memmove(&leds[0], &ledstemp[0], NUM_LEDS * sizeof(CRGB));
	OutputToLEDDisplayMode(); //crop the LED-Output
	OutputToLEDDisplayInfo(); //show button pressed info

	FastLED.show();
}

//Crop the LED Output to fit the Display Mode Left/Right/Night/All
void OutputToLEDDisplayMode()
{
	static uint16_t dot = 0;
	if (Settings.LedEffects[Settings.EffectNumber].DisplayMode == Left)
		fill_solid(&leds[NumberLEDLeft], NUM_LEDS-NumberLEDLeft, CHSV(0, 0, 0));
	if (Settings.LedEffects[Settings.EffectNumber].DisplayMode == Right)
		fill_solid(leds, NUM_LEDS - (NumberLEDRight-1), CHSV(0, 0, 0));
	if (Settings.LedEffects[Settings.EffectNumber].DisplayMode == Night)
	{
		for (dot = 0; dot < NUM_LEDS; dot=dot+1)
		{
			if (dot%Settings.LedEffects[Settings.EffectNumber].NightNumber)
				leds[dot] = CRGB::Black;
		}
	}
}

//Show info-bargraph on the left side of the LED-Strip
void OutputToLEDDisplayInfo()
{
	static uint8_t counter = 0;
	
	//if the state of the variable to show infos on the LEDs went true
	if (SettingsNow.ShowACK)
	{
		counter = 25;
		SettingsNow.ShowACK = 0;
		#if defined (DEBUGMODE)
		Serial.println("OutputToLED | DisplayInfo updated ");
		#endif // DEBUG
	}

	if (counter > 0)
	{
		//display info
		if (SettingsNow.ShowPercentage > 0)
		{
			fill_solid(leds, SettingsNow.ShowPercentage / 10, CRGB::Green);
			fill_solid(&(leds[SettingsNow.ShowPercentage / 10]), 25-(SettingsNow.ShowPercentage / 10) , CRGB::Black);
			leds[25] = CRGB::Red;
		}
		else
		{
			leds[1] = CRGB::Green;
			leds[2] = CRGB::Red;
		}
		leds[0] = CRGB::Red;

		//decrease the counter-display time
		EVERY_N_MILLISECONDS(100)
		{
			counter = counter - 1;
			if (counter == 0)
				SettingsNow.ShowPercentage = 0;
		}

	}
}
