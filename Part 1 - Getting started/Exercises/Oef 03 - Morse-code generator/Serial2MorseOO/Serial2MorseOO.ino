#include "Ascii2MorseBeep.h"

Ascii2Morse morseEncoder(5, 50);	
							// create an encoder object. Give it 'global' scope
							// morseEncoder(pinOut, durationShort)
							// pinOut = hardware pin to send the morse code out
							// durationShort = # ms for a 'short' bit.

void setup()
	{
	Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps	
	}

void loop()
	{
    if (Serial.available() > 0)
    	{
        morseEncoder.send(Serial.read());
        }	
	}
