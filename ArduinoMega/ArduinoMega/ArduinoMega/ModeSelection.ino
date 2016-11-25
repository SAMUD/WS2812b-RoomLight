void ModeSelectionMain()
{
	
	//needs only to be run every 50ms because values from other Arduino are also only read each 50ms
	EVERY_N_MILLISECONDS(49)
	{
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == FuncStop)
		{
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!LEDSettings.PowerState)
				ModeSelectionTurnOn();
			else
			{
				//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
				switch (LEDSettings.DisplayMode)
				{
				case WhiteAll:
					LEDSettings.DisplayMode = WhiteLeft;
					Serial.println("ModeSelectionMain | Changed to WhiteLeft-Mode");
					break;
				case WhiteLeft:
					LEDSettings.DisplayMode = WhiteRight;
					Serial.println("ModeSelectionMain | Changed to WhiteRight-Mode");
					break;
				default:
					LEDSettings.DisplayMode = WhiteAll;
					Serial.println("ModeSelectionMain | Changed to WhiteAll-Mode");
					break;
				}
				LEDSettings.ChangesToEffectMade = 1;
			}

		}

		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Eight)
		{
			//If LEDS are off, turn them on with the last mode. else get the new one
			if (!LEDSettings.PowerState)
				ModeSelectionTurnOn();
			else
			{
				//switching to the next mode (WhiteAll --> WhiteLeft --> WhiteRight -->)
				switch (LEDSettings.DisplayMode)
				{
				/*case WhiteAll:
					LEDSettings.DisplayMode = WhiteLeft;
					Serial.println("ModeSelectionMain | Changed to WhiteLeft-Mode");
					break;
				case WhiteLeft:
					LEDSettings.DisplayMode = WhiteRight;
					Serial.println("ModeSelectionMain | Changed to WhiteRight-Mode");
					break;*/
				default:
					LEDSettings.DisplayMode = Confetti;
					Serial.println("ModeSelectionMain | Changed to Confetti-Mode");
					break;
				}
				LEDSettings.ChangesToEffectMade = 1;
			}

		}

		//change to turn all on
		if (ReadValues.newValues == 1 && ReadValues.ButtonPressed == Nine)
		{
			//making full white
			LEDSettings.DisplayMode = WhiteAll;
			LEDSettings.BrightnessSetpoint = 255;
			LEDSettings.Saturation = 0;
			LEDSettings.Hue = 0;
			if (!LEDSettings.PowerState)
				LEDSettings.PowerState = 1;

		}
	}
	
}

//used to turn on the LEDs if they are off and I press a mode button
void ModeSelectionTurnOn()
{
	Serial.println("ModeSelectionMain | Turned on LEDs");
	LEDSettings.PowerState = 1;
	LEDSettings.DisplayMode = LEDSettings.DisplayModeOld;
	//BrightnessTurnOn();
}
