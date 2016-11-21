


void BrightnessMain()
{
	
	if (ReadValues.ButtonPressed == VolDown && (ReadValues.newValues || ReadValues.Repeat))
	{
		if (ReadValues.Repeat == 1 && LEDSettings.BrightnessSetpoint > 5)  //Fast scaling
		{
			LEDSettings.BrightnessSetpoint = LEDSettings.BrightnessSetpoint -5;
			Serial.print("----  ");
		}
			
		else if (LEDSettings.BrightnessSetpoint > 5) //Slow scaling
		{
			LEDSettings.BrightnessSetpoint = LEDSettings.BrightnessSetpoint-5;
			Serial.print("--    ");
		}
		else
			Serial.print("oo    ");

		Serial.print("BrightnessDown [Setpoint  Actual]");
		Serial.print(LEDSettings.BrightnessSetpoint);
		Serial.print(" ");
		Serial.println(FastLED.getBrightness());

	}
	if (ReadValues.ButtonPressed == VolUp && (ReadValues.newValues || ReadValues.Repeat))
	{
		if (ReadValues.Repeat == 1 && LEDSettings.BrightnessSetpoint < 251) //Fast scaling
		{
			LEDSettings.BrightnessSetpoint = LEDSettings.BrightnessSetpoint +5;
			Serial.print("++++  ");

		}
		else if (LEDSettings.BrightnessSetpoint < 251)
		{
			LEDSettings.BrightnessSetpoint = LEDSettings.BrightnessSetpoint +5; //Slow scaling
			Serial.print("++    ");
		}
		else
			Serial.print("oo    ");
		Serial.print("BrightnessUp Setpoint  Actual");
		Serial.print(LEDSettings.BrightnessSetpoint);
		Serial.print(" ");
		Serial.println(FastLED.getBrightness());
	}

	BrightnessFade(LEDSettings.BrightnessSetpoint);
	

}

//Fading the Brightness to the Value specified in LEDSettings.BrightnessSetpoint
void BrightnessFade(uint8_t Setpoint)
{
	uint8_t incrementor = 0;
	
	//when Setpoint is not the same as actual brightness
	incrementor = 1;
	if (FastLED.getBrightness() - Setpoint > 5 || FastLED.getBrightness() - Setpoint < -5)
		incrementor = 2;
	if (FastLED.getBrightness() - Setpoint > 10 || FastLED.getBrightness() - Setpoint < -10)
		incrementor = 5;
	if (FastLED.getBrightness() - Setpoint > 20 || FastLED.getBrightness() - Setpoint < -20)
		incrementor = 10;
	if (FastLED.getBrightness() - Setpoint > 40 || FastLED.getBrightness() - Setpoint < -40)
		incrementor = 20;

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
		BrightnessFade(0);
		FastLED.show();
		delay(40);
		Serial.print("-");
	}
	Serial.println("Powered down now");
}

//Turning on the LED-Strip
void BrightnessTurnOn()
{
	while (FastLED.getBrightness() != LEDSettings.BrightnessSetpoint)
	{
		//run BrightnessFade until brightness is 0
		BrightnessFade(LEDSettings.BrightnessSetpoint);
		FastLED.show();
		delay(40);
		Serial.print("+");
	}
	Serial.println("Powered on now");
}

