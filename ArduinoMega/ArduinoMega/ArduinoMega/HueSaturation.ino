static uint16_t Value=255;

//TODO: implement fast scaling 

void HueSaturationMain()
{
	
	EVERY_N_MILLISECONDS(50)
	{
		if (
			(LEDSettings.DisplayMode == WhiteAll || LEDSettings.DisplayMode == WhiteLeft || LEDSettings.DisplayMode == WhiteRight) &&
			(ReadValues.newValues == 1 || ReadValues.Repeat == 1) &&
			ReadValues.ButtonPressed == Forward)
		{

			HueSaturationReadHueSaturation(); //read and write to 'Value'
			
			if (Value < (510 - 100) && ReadValues.Repeat == 0)
				Value = Value + 1; //slow Increase
			else if (Value < (510 - 100) && ReadValues.Repeat)
				Value = Value + 3; //fast Increase
			
			//set the new values();
			HueSaturationSetHue();
			HueSaturationSetSaturation();
			LEDSettings.ChangesToEffectMade = 1;

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
			HueSaturationReadHueSaturation(); //read and write to 'Value'
			
			if (Value > 150 && ReadValues.Repeat == 0)
				Value = Value - 1; //slow Increase
			else if (Value > 152 && ReadValues.Repeat)
				Value = Value - 3; //fast Increase

			//set the new values
			HueSaturationSetHue();
			HueSaturationSetSaturation();
			LEDSettings.ChangesToEffectMade = 1;

			Serial.print("Decreasing ColorTemp [Hue Saturation]  ");
			Serial.print(LEDSettings.Hue);
			Serial.print(" ");
			Serial.println(LEDSettings.Saturation);
		}
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

void HueSaturationReadHueSaturation()
{
	Value = LEDSettings.Saturation;

	if (LEDSettings.Hue == 0)
		Value = Value + 255;
}
