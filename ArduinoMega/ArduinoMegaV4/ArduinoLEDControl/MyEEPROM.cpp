// 
// 
// 

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
	EEPROM.readBlock(ConfigAdress, Settings);
	return (Settings.MemoryVersion == DMemoryVersion);
}

void EEPROMsaveDefaultValues()
{
	Settings.Current->BrightnessSetpoint = 128;
	Settings.Current->DisplayMode == All;
	Settings.Current->NightNumber = 3;
	Settings.Current->Saturation = 255;
	Settings.Current->Speed = 1;
	Settings.Current->Temperature == Halogen2;

	//store the stock values into the EEPROM if nothing was there
	EEPROMsave();

}

void EEPROMsave()
{
	EEPROM.updateBlock(ConfigAdress, Settings);
#if defined(DEBUGMODE)
	Serial.println("EEPROM | Saved Settings");
	Serial.println(Settings.Current->BrightnessSetpoint);
#endif
}