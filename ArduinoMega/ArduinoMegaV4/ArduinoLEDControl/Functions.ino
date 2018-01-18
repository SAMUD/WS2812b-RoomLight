void BlinkLed(uint16_t LEDdelay, uint16_t LEDTimeOn)
{
	static unsigned long millistemp;
	static bool state;

	if (SettingsNow.ShowACK == 1 || SettingsNow.ShowPercentage > 0)
	{
		//blink very fast
		LEDdelay = 10;
		LEDTimeOn = 10;
	}

	if (((millis() - millistemp > 100) && state == 0) || ((millis() - millistemp > 100) && state == 1))
	{
		millistemp = millis();
		state = !state;
		digitalWrite(13, state);
	}
}
