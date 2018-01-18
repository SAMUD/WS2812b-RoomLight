
/**
* @brief This will test if the Button passed in parameters has been pressed and change values accordingly
* 
* @param PassedPressedButton Which button has to be pressed to make -
* @param PassedPressedButtonPlus Which button has to be pressed to do +
* @param PassedRepeatAllowed Can this value be changed by holding down the Button?
* @param PassedValueToChange Pointer pointing to the Value which should be changed
* @param PassedMinAllowed The minimal value possible
* @param PassedMaxAllowed The maximal value allowed
* @param PassedSlowScaling The number of increments to do when doing a simle press
* @param PassedFastScaling The number of increments if fast scaling. Only needed when @p PassedRepeatAllowed is set to true
*/
void ChangeParamMain(uint8_t PassedPressedButton, uint8_t PassedPressedButtonPlus, bool PassedRepeatAllowed, uint8_t *PassedValueToChange, uint8_t PassedMinAllowed, uint8_t PassedMaxAllowed, uint8_t PassedSlowScaling, uint8_t PassedFastScaling  )
{
	//Test if the Button has been Pressed
	if (ReadValues.ButtonPressed == PassedPressedButton && (ReadValues.newValues || (ReadValues.Repeat && PassedRepeatAllowed)))
	{
		//Do Fast Scaling when holding down the Button
		if (ReadValues.Repeat == 1)
		{
			if (*PassedValueToChange > (PassedMinAllowed+PassedFastScaling) )
			{
				*PassedValueToChange = *PassedValueToChange - PassedFastScaling;
				#if defined(DEBUGMODE)
				Serial.print("----  ");
				#endif
			}
			else
			{
				*PassedValueToChange = PassedMinAllowed;
				#if defined(DEBUGMODE)
				Serial.print("oo    ");
				#endif			
			}
		}
		else //Slow scaling
		{
			if (*PassedValueToChange > (PassedMinAllowed + PassedSlowScaling))
			{
				*PassedValueToChange = *PassedValueToChange - PassedSlowScaling;
				#if defined(DEBUGMODE)
				Serial.print("--    ");
				#endif
			}
			else
			{
				*PassedValueToChange = PassedMinAllowed;
				#if defined(DEBUGMODE)
				Serial.print("oo    ");
				#endif
			}
		}

		SettingsNow.ChangesToEffectMade = true;
		#if defined(DEBUGMODE)
		Serial.print("ChangeParam | :");
		Serial.println(*PassedValueToChange);
		#endif
		//show status update
		SettingsNow.ShowACK = 1;
		SettingsNow.ShowPercentage = *PassedValueToChange * (255/PassedMaxAllowed);
		ReadValues.newValues = 0;
	}

	//Test if the + Button has been Pressed
	if (ReadValues.ButtonPressed == PassedPressedButtonPlus && (ReadValues.newValues || (ReadValues.Repeat && PassedRepeatAllowed)))
	{
		//Do Fast Scaling when holding down the Button
		if (ReadValues.Repeat == 1)
		{
			if (*PassedValueToChange < (PassedMaxAllowed - PassedFastScaling))
			{
				*PassedValueToChange = *PassedValueToChange + PassedFastScaling;
				#if defined(DEBUGMODE)
				Serial.print("----  ");
				#endif
			}
			else
			{
				*PassedValueToChange = PassedMaxAllowed;
				#if defined(DEBUGMODE)
				Serial.print("oo    ");
				#endif			
			}
		}
		else //Slow scaling
		{
			if (*PassedValueToChange < (PassedMaxAllowed - PassedSlowScaling))
			{
				*PassedValueToChange = *PassedValueToChange + PassedSlowScaling;
				#if defined(DEBUGMODE)
				Serial.print("--    ");
				#endif
			}
			else
			{
				*PassedValueToChange = PassedMaxAllowed;
				#if defined(DEBUGMODE)
				Serial.print("oo    ");
				#endif
			}
		}

		SettingsNow.ChangesToEffectMade = true;
		#if defined(DEBUGMODE)
		Serial.print("ChangeParam | :");
		Serial.println(*PassedValueToChange);
		#endif
		//show status update
		SettingsNow.ShowACK = 1;
		SettingsNow.ShowPercentage = *PassedValueToChange * (255 / PassedMaxAllowed);
		ReadValues.newValues = 0;
	}
}
