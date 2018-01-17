// 
// 
// 

#include "EEPROMLib.h"

static int ConfigAdress = 0;

void EEPROMinit(StoreStruct *SettingEEPROM)
{
	EEPROM.setMemPool(32, EEPROMSizeMega);
	ConfigAdress = EEPROM.getAddress(sizeof(*SettingEEPROM));

	if (!EEPROMloadConfig(SettingEEPROM))
	{
		//Konfiguration was lost. Initialize
		// TODO: show something, that we are rebuilding the Konfiguration
		#ifdef DEBUGMODE
			Serial.println("EEPROM: Memory is invalid. Rebuilding config now.");
		#endif
		EEPROMsaveDefaultValues(SettingEEPROM);
	}
	else
	{
		#ifdef DEBUGMODE
			Serial.println("EEPROM: Memory is valid.");
		#endif
	}
}

bool EEPROMloadConfig(StoreStruct *SettingEEPROM)
{
	EEPROM.readBlock(ConfigAdress, *SettingEEPROM);
	return (SettingEEPROM->MemoryVersion == DMemoryVersion);
}

void EEPROMsaveDefaultValues(StoreStruct *SettingEEPROM)
{
	SettingEEPROM->Current = &(SettingEEPROM->White[0]);

	SettingEEPROM->Current->BrightnessSetpoint	= 255;
	SettingEEPROM->Current->Color				= 0;
	SettingEEPROM->Current->DisplayMode			== All;
	SettingEEPROM->Current->NightNumber			= 5;
	SettingEEPROM->Current->Saturation			= 255;
	SettingEEPROM->Current->Set					= 127;
	SettingEEPROM->Current->Speed				= 127;
	SettingEEPROM->Current->Temperature			== DirectSunlight2;
	SettingEEPROM->Current->Name				= "White0";


	//store the stock values into the EEPROM if nothing was there
	SettingEEPROM->FixedColor[0]				= (SettingEEPROM->White[0]);
	SettingEEPROM->FixedColor[1]				= (SettingEEPROM->White[0]);
	SettingEEPROM->FixedColor[2]				= (SettingEEPROM->White[0]);
	SettingEEPROM->FixedColor[3]				= (SettingEEPROM->White[0]);
	SettingEEPROM->White[0]						= (SettingEEPROM->White[0]);
	SettingEEPROM->White[1]						= (SettingEEPROM->White[0]);
	SettingEEPROM->White[2]						= (SettingEEPROM->White[0]);
	SettingEEPROM->Confetti[0]					= (SettingEEPROM->White[0]);
	SettingEEPROM->Confetti[1]					= (SettingEEPROM->White[0]);
	SettingEEPROM->RainbowMarch					= (SettingEEPROM->White[0]);
	SettingEEPROM->RainbowBeat					= (SettingEEPROM->White[0]);
	SettingEEPROM->ColorPalBeat					= (SettingEEPROM->White[0]);
	SettingEEPROM->Fade							= (SettingEEPROM->White[0]);
	SettingEEPROM->RGBFade						= (SettingEEPROM->White[0]);
	SettingEEPROM->Strobe						= (SettingEEPROM->White[0]);
	SettingEEPROM->Ball							= (SettingEEPROM->White[0]);

	SettingEEPROM->FixedColor[0].Name			= "FixedColor0";
	SettingEEPROM->FixedColor[1].Name			= "FixedColor1";
	SettingEEPROM->FixedColor[2].Name			= "FixedColor2";
	SettingEEPROM->FixedColor[3].Name			= "FixedColor3";
	SettingEEPROM->White[1].Name				= "White1";
	SettingEEPROM->White[2].Name				= "White2";
	SettingEEPROM->Confetti[0].Name				= "Confetti0";
	SettingEEPROM->Confetti[1].Name				= "Confetti1";
	SettingEEPROM->RainbowMarch.Name			= "RainbowMarch";
	SettingEEPROM->RainbowBeat.Name				= "RainbowBeat";
	SettingEEPROM->ColorPalBeat.Name			= "ColorPalBeat";
	SettingEEPROM->Fade.Name					= "Fade";
	SettingEEPROM->RGBFade.Name					= "RGBFade";
	SettingEEPROM->Strobe.Name					= "Strobe";
	SettingEEPROM->Ball.Name					= "Ball";

	SettingEEPROM->MemoryVersion = DMemoryVersion;

	EEPROMsave(SettingEEPROM);

}

void EEPROMsave(StoreStruct *SettingEEPROM)
{
	EEPROM.updateBlock(ConfigAdress,*SettingEEPROM);
	#ifdef DEBUGMODE
		Serial.println("EEPROM | Saved SettingsEEPROM");
	#endif
		
}