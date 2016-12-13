void BrightnessMain()
{
	EVERY_N_MILLISECONDS(50)
	{
		if (ReadValues.ButtonPressed == VolDown && (ReadValues.newValues || ReadValues.Repeat))
		{
			if (ReadValues.Repeat == 1)  //Fast scaling
			{
				if (LEDSettings.BrightnessSetpoint > 10)
				{
					LEDSettings.BrightnessSetpoint = LEDSettings.BrightnessSetpoint - 10;
					#if defined(DEBUGMODE)
					Serial.print("----  ");
					#endif
				}
				else
				{
					LEDSettings.BrightnessSetpoint = 5;
					#if defined(DEBUGMODE)
					Serial.print("oo    ");
					#endif			
				}
			}
			else //Slow scaling
			{
				if (LEDSettings.BrightnessSetpoint > 5)
				{
					LEDSettings.BrightnessSetpoint = LEDSettings.BrightnessSetpoint - 5;
					#if defined(DEBUGMODE)
					Serial.print("--    ");
					#endif
				}
				else
				{
					LEDSettings.BrightnessSetpoint = 5;
					#if defined(DEBUGMODE)
					Serial.print("oo    ");
					#endif
				}
			}

			LEDSettings.ChangesToEffectMade = 1;
			#if defined(DEBUGMODE)
			Serial.print("BrightnessMain | Down [Setpoint  Actual]");
			Serial.print(LEDSettings.BrightnessSetpoint);
			Serial.print(" ");
			Serial.println(FastLED.getBrightness());
			#endif
			ReadValues.newValues = 0;
		}
		if (ReadValues.ButtonPressed == VolUp && (ReadValues.newValues || ReadValues.Repeat))
		{
			if (ReadValues.Repeat == 1) //Fast scaling
			{
				
				if (LEDSettings.BrightnessSetpoint < 246)
				{
					LEDSettings.BrightnessSetpoint = LEDSettings.BrightnessSetpoint + 10;
					#if defined(DEBUGMODE)
					Serial.print("++++  ");
					#endif
				}
				else
				{
					LEDSettings.BrightnessSetpoint = 255;
					#if defined(DEBUGMODE)
					Serial.print("oo    ");
					#endif
				}
			}
			else
			{
				if (LEDSettings.BrightnessSetpoint < 240)
				{
					LEDSettings.BrightnessSetpoint = LEDSettings.BrightnessSetpoint + 5; //Slow scaling
					#if defined(DEBUGMODE)
					Serial.print("++    ");
					#endif
				}
				else
				{
					LEDSettings.BrightnessSetpoint = 255; //Slow scaling
					#if defined(DEBUGMODE)
					Serial.print("oo    ");
					#endif
				}
				
			}

			LEDSettings.ChangesToEffectMade = 1;
			#if defined(DEBUGMODE)
			Serial.print("BrightnessMain | Up Setpoint  Actual");
			Serial.print(LEDSettings.BrightnessSetpoint);
			Serial.print(" ");
			Serial.println(FastLED.getBrightness());
			#endif
			ReadValues.newValues = 0;
		}
	}
	
	BrightnessFade(LEDSettings.BrightnessSetpoint);
	

}

//Fading the Brightness to the Value specified in LEDSettings.BrightnessSetpoint
void BrightnessFade(uint8_t Setpoint)
{
	EVERY_N_MILLISECONDS(20) //run at 66Hz to have seamles blending
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
			//show_at_max_brightness_for_power();
			FastLED.show();
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
	while (FastLED.getBrightness() != LEDSettings.BrightnessSetpoint)
	{
		//run BrightnessFade until brightness is = Setpoint
		EVERY_N_MILLISECONDS(40)
		{
			BrightnessFade(LEDSettings.BrightnessSetpoint);
			//show_at_max_brightness_for_power();
			FastLED.show();
		}
		BlinkLed(10, 100);
	}
	#if defined(DEBUGMODE)
	Serial.println("BrightnessTurnOn | Powered on now");
	#endif
}

