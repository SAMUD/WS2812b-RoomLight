//Fading the Brightness to the Value specified in LEDSetLedBlock.BrightnessSetpoint
void BrightnessFade(uint8_t Setpoint)
{
	uint8_t incrementor = 0;

	//when Setpoint is not the same as actual brightness
	incrementor = 1;
	if (FastLED.getBrightness() - Setpoint > 10 || FastLED.getBrightness() - Setpoint < -10)
		incrementor = 2;
	if (FastLED.getBrightness() - Setpoint > 20 || FastLED.getBrightness() - Setpoint < -20)
		incrementor = 4;
	if (FastLED.getBrightness() - Setpoint > 30 || FastLED.getBrightness() - Setpoint < -30)
		incrementor = 8;
	if (FastLED.getBrightness() - Setpoint > 40 || FastLED.getBrightness() - Setpoint < -40)
		incrementor = 16;
	if (FastLED.getBrightness() - Setpoint > 70 || FastLED.getBrightness() - Setpoint < -70)
		incrementor = 32;

	if (FastLED.getBrightness() < Setpoint)
		FastLED.setBrightness(FastLED.getBrightness() + incrementor);

	if (FastLED.getBrightness() > Setpoint)
		FastLED.setBrightness(FastLED.getBrightness() - incrementor);
}

//Turning off the LED-Strip
void BrightnessTurnOff()
{
	
	while (FastLED.getBrightness() > 0)
	{
		//run BrightnessFade until brightness is 0
		EVERY_N_MILLISECONDS(30)
		{
			BrightnessFade(0);
			OutputToLEDMain();
		}
		BlinkLed(100, 10);
	}
	#if defined(DEBUGMODE)
		Serial.println("BrightnessTurnOff | Powered down now");
	#endif
}

//Turning on the LED-Strip
void BrightnessTurnOn()
{
	while (FastLED.getBrightness() != SetLedBlock.Current.BrightnessSetpoint)
	{
		//run BrightnessFade until brightness is = Setpoint
		EVERY_N_MILLISECONDS(40)
		{
			BrightnessFade(SetLedBlock.Current.BrightnessSetpoint);
			//show_at_max_brightness_for_power();
			FastLED.show();
		}
		BlinkLed(10, 100);
	}
	
	#if defined(DEBUGMODE)
		Serial.println("BrightnessTurnOn | Powered on now");
	#endif
}
