

#define PINValueChanged 36
#define PINMultiplePresses 34
#define PINInput1 30						//The LSB-Bit
#define PINInput2 28
#define PINInput3 26
#define PINInput4 24
#define PINInput5 22						//The MSB-Bit

//used for the White Effects
#define NumberLEDLeft 2
#define NumberLEDRight 2
#define NumberLEDTransition 2
#define ValueLEDDarkside 75


enum Buttons
{
	Zero, One, Two, Three, Four, Five, Six,Seven, Eight, Nine,
	Power, VolUp, FuncStop, Reward, PlayPause, Forward, Down, VolDown, Up, Eq, StRept,
	Nothing
};

enum Mode
{
	None,
	WhiteLeft,WhiteRight,WhiteAll
};

static struct Values
{
	Buttons ButtonPressed;
	bool Repeat;
	bool newValues;
}ReadValues;

static struct Settings
{
	uint8_t BrightnessSetpoint;
	bool PowerState;
	Mode DisplayMode;
	Mode DisplayModeOld;
	uint8_t Hue;
	uint8_t Saturation;
}LEDSettings;