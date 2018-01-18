void BlinkLed(uint16_t LEDdelay, uint16_t LEDTimeOn)
{
	static unsigned long millistemp;
	static bool state;
	
	if (SettingsNow.ShowACK == 1 || SettingsNow.ShowPercentage > 0)
	{
		//blink very fast
		LEDdelay = 50;
		LEDTimeOn = 50;
	}

	if ( ((millis() - millistemp > LEDdelay) && state==0) || ((millis() - millistemp > LEDTimeOn) && state == 1))
	{
		millistemp = millis();
		state = !state;
		digitalWrite(13, state);
	}
}
