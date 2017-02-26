#include <EEPROMex.h>

void EEPROMinit()
{
	EEPROM.setMemPool(32, EEPROMSizeMega);
	configAdress = EEPROM.getAddress(sizeof(Settings));
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
	EEPROM.readBlock(configAdress, Settings);
	return (Settings.MemoryVersion == DMemoryVersion);
}

void EEPROMsaveDefaultValues()
{
	Settings.Current.BrightnessSetpoint = 128;
	Settings.Current.DisplayMode = All;
	Settings.Current.NightNumber = 3;
	Settings.Current.Saturation = 255;
	Settings.Current.SpeedColor = 1;
	Settings.Current.Temperature = Halogen2;
	
	//store the stock values into the EEPROM if nothing was there
	Settings.ChangesToEffectMade = 1;
	Settings.DisplayMode = White;
	Settings.DisplayModeOld = None;
	Settings.PowerState = 1;
	Settings.PlayPause = 1;
	Settings.ColorPalBeat = Settings.Current;
	Settings.Confetti = Settings.Current;
	Settings.ConfettiColorfull = Settings.Current;
	Settings.Fade = Settings.Current;
	Settings.FixedColor = Settings.Current;
	Settings.FixedColor2 = Settings.Current;
	Settings.FixedColor3 = Settings.Current;
	Settings.White = Settings.Current;
	Settings.White2 = Settings.Current;
	Settings.Strobe = Settings.Current;
	Settings.RGBFade = Settings.Current;
	Settings.RainbowMarch = Settings.Current;
	Settings.RainbowBeat = Settings.Current;
	Settings.Ball = Settings.Current;
	Settings.MemoryVersion = DMemoryVersion;
	EEPROMsave();

}

void EEPROMsave()
{
	EEPROM.updateBlock(configAdress, Settings);
	#if defined(DEBUGMODE)
	Serial.println("EEPROM | Saved settings");
	Serial.println(Settings.Current.BrightnessSetpoint);
	#endif
}