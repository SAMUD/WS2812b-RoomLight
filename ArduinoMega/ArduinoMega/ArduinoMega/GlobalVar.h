






//In Out Pins used on my Arduino
#define PINValueChanged 36
#define PINMultiplePresses 34
#define PINInput1 30						//The LSB-Bit coming from the other Arduino
#define PINInput2 28
#define PINInput3 26
#define PINInput4 24
#define PINInput5 22						//The MSB-Bit coming from the other Arduino

//used for WhiteLeft and WhiteRight
#define NumberLEDLeft 100
#define NumberLEDRight 100
#define NumberLEDTransition 25
#define ValueLEDDarkside 100

//The Buttons which are availaible on my Transmitter
/*	Zero=
	Zero= 
	One= 
	Two=
	Three=
	Four=
	Five=
	Six=
	Seven=
	Eight=
	Nine=		turn all leds on at full brightness even when other settings where specified before
	Power=		Turn the strip on/off
	VolUp=		Brightness+
	FuncStop=	change Between White Modes --> White All, WhiteLeft, WhiteRight
	Reward=		in all White-Modes: Temperature-
	PlayPause=
	Forward=	in all White-Modes: Temperature+
	Down=
	VolDown=	Brightness-
	Up=
	Eq=
	StRept=
	Nothing=Enum default state at bootup
*/
enum Buttons
{
	Zero, One, Two, Three, Four, Five, Six,Seven, Eight, Nine,
	Power, VolUp, FuncStop, Reward, PlayPause, Forward, Down, VolDown, Up, Eq, StRept,
	Nothing
};

//enum with the actual Mode
enum Mode
{
	None,
	WhiteLeft,WhiteRight,WhiteAll,
	Confetti, RainbowMarch
};

//structure with the values read from the other Arduino
static struct Values
{
	Buttons ButtonPressed;
	bool Repeat;
	bool newValues;
}ReadValues;

//All Settings used at the moment
//will later be saved in the EEPROM
static struct Settings
{
	uint8_t BrightnessSetpoint;		//Setpoint for the Brightness
	bool PowerState;				//true=On False=off
	Mode DisplayMode;				//the Actual Mode
	Mode DisplayModeOld;			//the Old mode
	uint8_t Hue;					//used in Temperature Settings
	uint8_t Saturation;				//used in Temperature Settings
	uint8_t ChangesToEffectMade;		//when the LEDS need to be redrwan, cause there were changes to the effects 
}LEDSettings;