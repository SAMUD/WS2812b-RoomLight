#include <EEPROMex.h>

static int configAdress = 0;

void EEPROMinit()
{
	EEPROM.setMemPool(32, EEPROMSizeMega);
	configAdress = EEPROM.getAddress(sizeof(Settings));
	
	//TODO
	if (!EEPROMloadConfig())
	{
		EEPROMsaveDefaultValues();
		//Serial print
		#if defined(DEBUGMODE)
		Serial.println("EEPROM: Invalid Memory. Restoring stock values");
		#endif
	}
	else
	{
		#if defined(DEBUGMODE)
		Serial.println("EEPROM: Valid Memory.");
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
	Settings.EffectNumber = 0;

	for (int i = 0; i <= NUMBEREFFECTS; i++)
	{
		Settings.LedEffects[i].BrightnessSetpoint = 128;
		Settings.LedEffects[i].DisplayMode == All;
		Settings.LedEffects[i].NightNumber = 3;
		Settings.LedEffects[i].Saturation = 127;
		Settings.LedEffects[i].Speed = 1;
		Settings.LedEffects[i].Temperature == Candle2;
		Settings.LedEffects[i].Color = 0;
		Settings.LedEffects[i].NumberEffect = i;
	}

	Settings.MemoryVersion = DMemoryVersion;
	EEPROMsave();

}

void EEPROMsave()
{
	EEPROM.updateBlock(configAdress, Settings);
	#if defined(DEBUGMODE)
	Serial.println("EEPROM: Saved settings");
	Serial.println(Settings.LedEffects[Settings.EffectNumber].BrightnessSetpoint);
	#endif
}