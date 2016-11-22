void DisplayEffectMain()
{
	if (LEDSettings.DisplayMode != LEDSettings.DisplayModeOld)
	{
		LEDSettings.DisplayModeOld = LEDSettings.DisplayMode;
		DisplayEffectTransition();
	}

	if (LEDSettings.DisplayMode == WhiteAll)
		DisplayEffectWhiteAll();
	else if (LEDSettings.DisplayMode == WhiteLeft)
		DisplayEffectWhiteLeft();
	else if (LEDSettings.DisplayMode == WhiteRight)
		DisplayEffectWhiteRight();
}

void DisplayEffectTransition()
{

}

void DisplayEffectWhiteAll()
{
	//Serial.println("EffectWhiteAll");
	for (int dot = 0; dot < NUM_LEDS; dot++)
	{
		leds[dot] = CHSV(LEDSettings.Hue+42, LEDSettings.Saturation,255);
		FastLED.show();
		//clear this led for the next time around the loop
		//leds[dot] = CRGB::Black;
		//delay(30);
		
	}
}

void DisplayEffectWhiteLeft()
{
	float temp;
	uint8_t temp2;
	//Serial.println("EffectWhiteLeft");
	for (int dot = 0; dot < NUM_LEDS; dot++)
	{
		if (dot < NumberLEDLeft)
		{
			leds[dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation,255);
		}
		else if (dot < NumberLEDLeft + NumberLEDTransition)
		{
			temp = ((NumberLEDLeft+NumberLEDTransition) - dot)/10.0;
			//Serial.print("temp:");
			//Serial.print(temp);
			temp2 = (255);
			//Serial.print(" temp2:");
			//Serial.print(temp2);
			temp = temp2 * temp;
			//Serial.print(" final:");
			//Serial.println(temp);
			
			leds[dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, temp+ValueLEDDarkside);
		}
		else
		{
			leds[dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, ValueLEDDarkside);
		}


	}
}

void DisplayEffectWhiteRight()
{
	float temp3;
	uint8_t temp4;
	//Serial.println("EffectWhiteRight");
	for (int dot = 1; dot <= NUM_LEDS; dot++)
	{
		if (dot < NumberLEDRight)
		{
			leds[NUM_LEDS - dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, 255);
		}
		else if (dot < NumberLEDRight + NumberLEDTransition+1)
		{
			temp3 = ((NumberLEDRight + NumberLEDTransition+1) - dot) / 10.0;
			//Serial.print("temp:");
			//Serial.print(temp);
			temp4 = (255);
			//Serial.print(" temp2:");
			//Serial.print(temp2);
			temp3 = temp4 * temp3;
			//Serial.print(" final:");
			//Serial.println(temp);

			leds[NUM_LEDS-dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, temp3 + ValueLEDDarkside);
		}
		else
		{
			leds[NUM_LEDS - dot] = CHSV(LEDSettings.Hue + 42, LEDSettings.Saturation, ValueLEDDarkside);
		}


	}


}