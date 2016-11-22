static uint16_t Value=255;

void HueSaturationMain()
{
	

	if (
		(LEDSettings.DisplayMode ==WhiteAll || LEDSettings.DisplayMode == WhiteLeft ||LEDSettings.DisplayMode == WhiteRight) &&
		(ReadValues.newValues == 1 || ReadValues.Repeat == 1) &&
		ReadValues.ButtonPressed == Forward)
	{
		
		if (Value < ((255 * 2)-100))
			Value = Value + 1;
		HueSaturationSetHue();
		HueSaturationSetSaturation();
		Serial.print("Increasing ColorTemp [Hue Saturation]  ");
		Serial.print(LEDSettings.Hue);
		Serial.print(" ");
		Serial.println(LEDSettings.Saturation);
		
	
	}

	if (
		(LEDSettings.DisplayMode == WhiteAll || LEDSettings.DisplayMode == WhiteLeft || LEDSettings.DisplayMode == WhiteRight) &&
		(ReadValues.newValues == 1 || ReadValues.Repeat == 1) &&
		ReadValues.ButtonPressed == Reward)
	{
		
		if (Value > 150)
			Value = Value - 1;
		HueSaturationSetHue();
		HueSaturationSetSaturation();	
		Serial.print("Decreasing ColorTemp [Hue Saturation]  ");
		Serial.print(LEDSettings.Hue);
		Serial.print(" ");
		Serial.println(LEDSettings.Saturation);
	}

}

void HueSaturationSetHue()
{
	if (Value > 255)
		LEDSettings.Hue = 0;
	else
		LEDSettings.Hue = 255 / 2;
}

void HueSaturationSetSaturation()
{
	if (Value > 255)
		LEDSettings.Saturation = Value - 255;
	else
		LEDSettings.Saturation = 255 - Value;
}
