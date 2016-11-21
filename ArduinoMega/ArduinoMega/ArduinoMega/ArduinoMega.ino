/*
 Name:		ArduinoMega.ino
 Created:	19.11.2016 15:37:27
 Author:	sdaur
*/

#include <FastLED.h>
#define NUM_LEDS 8
#define DATA_PIN 51

CRGB leds[NUM_LEDS];

// the setup function runs once when you press reset or power the board
void setup() {
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness(255);
}

int bright = 50;
uint8_t max_bright = 128;
uint8_t thisdelay = 50;                                        // A delay value for the sequence(s)
uint8_t thishue = 0;                                          // Starting hue value.
uint8_t deltahue = 8;

// the loop function runs over and over again until power down or reset
void loop() {
	EVERY_N_MILLISECONDS(thisdelay) {                           // FastLED based non-blocking routine to update/display the sequence.
		rainbow_march();

		FastLED.show();
	}
	
	/*for (int dot = 0; dot < NUM_LEDS; dot++) {
		leds[dot] = CRGB::PapayaWhip;
		FastLED.show();
		// clear this led for the next time around the loop
		//leds[dot] = CRGB::White;
		delay(30);
	}*/
		
	
}

void rainbow_march() {                                        // The fill_rainbow call doesn't support brightness levels
	//uint8_t beatA = beatsin16(5, 0, 255);                        // Starting hue
	//uint8_t beatB = beatsin16(15, 4, 20);   
	thishue++;    // Increment the starting hue.
	fill_rainbow(leds, NUM_LEDS, thishue, deltahue);            // Use FastLED's fill_rainbow routine.
	//fill_rainbow(leds, NUM_LEDS, beatA, beatB);
} // rainbow_march()