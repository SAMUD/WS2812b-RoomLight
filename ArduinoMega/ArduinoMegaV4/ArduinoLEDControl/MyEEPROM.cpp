
#include "MyEEPROM.h"
#include "GlobalVarLEDControl.h"
#include "EEPROMex.h"
#include "GlobalVar.h"

static int ConfigAdress = 0;


void EEPROMStart()
{
	EEPROM.setMemPool(32, EEPROMSizeMega);
	ConfigAdress = EEPROM.getAddress(sizeof(Settings));
	//TODO
	if (!EEPROMloadConfig())
	{
		//do something to show that config was lost
		//
		//store stock values in EEPROM
		//Serial print
		#if defined(DEBUGMODE)
				Serial.println("Memory is invalid");
		#endif
		EEPROMsaveDefaultValues();
		
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
	EEPROM.readBlock(ConfigAdress, Settings);
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

	//store the stock values into the EEPROM if nothing was there
	EEPROMsave();

}

void EEPROMsave()
{
	EEPROM.updateBlock(ConfigAdress, Settings);
#if defined(DEBUGMODE)
	Serial.println("EEPROM | Saved Settings");
	Serial.println(Settings.LedEffects[Settings.EffectNumber].BrightnessSetpoint);
#endif
}