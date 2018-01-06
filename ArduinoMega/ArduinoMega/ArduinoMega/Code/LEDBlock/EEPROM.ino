#include <EEPROMex.h>

void EEPROMinit()
{
	EEPROM.setMemPool(32, EEPROMSizeMega);
	configAdress = EEPROM.getAddress(sizeof(SetLedBlock));
	memValid = EEPROMloadConfig();
	//TODO
	if (!memValid)
	{
		//do something to show that config was lost
		//
		//store stock values in EEPROM
		EEPROMsaveDefaultValues();
		//Serial print
		#if defined(DEBUGMODE)
		Serial.println("Memory is invalid");
		#endif
	}
	else
	{
		#if defined(DEBUGMODE)
		Serial.println("Memory is valid.");
		#endif
	}

}

bool EEPROMloadConfig()
{
	EEPROM.readBlock(configAdress, SetLedBlock);
	return (SetLedBlock.MemoryVersion == DMemoryVersion);
}

void EEPROMsaveDefaultValues()
{
	SetLedBlock.Current.BrightnessSetpoint = 128;
	SetLedBlock.Current.DisplayMode = All;
	SetLedBlock.Current.NightNumber = 3;
	SetLedBlock.Current.Saturation = 255;
	SetLedBlock.Current.SpeedColor = 1;
	SetLedBlock.Current.Temperature = Halogen2;
	
	//store the stock values into the EEPROM if nothing was there
	SetLedBlock.ChangesToEffectMade = 1;
	SetLedBlock.DisplayMode = White;
	SetLedBlock.DisplayModeOld = None;
	SetLedBlock.PowerState = 1;
	SetLedBlock.PlayPause = 1;
	SetLedBlock.ColorPalBeat = SetLedBlock.Current;
	SetLedBlock.Confetti = SetLedBlock.Current;
	SetLedBlock.ConfettiColorfull = SetLedBlock.Current;
	SetLedBlock.Fade = SetLedBlock.Current;
	SetLedBlock.FixedColor = SetLedBlock.Current;
	SetLedBlock.FixedColor2 = SetLedBlock.Current;
	SetLedBlock.FixedColor3 = SetLedBlock.Current;
	SetLedBlock.White = SetLedBlock.Current;
	SetLedBlock.White2 = SetLedBlock.Current;
	SetLedBlock.Strobe = SetLedBlock.Current;
	SetLedBlock.RGBFade = SetLedBlock.Current;
	SetLedBlock.RainbowMarch = SetLedBlock.Current;
	SetLedBlock.RainbowBeat = SetLedBlock.Current;
	SetLedBlock.Ball = SetLedBlock.Current;
	SetLedBlock.MemoryVersion = DMemoryVersion;
	EEPROMsave();

}

void EEPROMsave()
{
	EEPROM.updateBlock(configAdress, SetLedBlock);
	#if defined(DEBUGMODE)
	Serial.println("EEPROM | Saved SetLedBlock");
	Serial.println(SetLedBlock.Current.BrightnessSetpoint);
	#endif
}