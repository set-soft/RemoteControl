#include <Arduino.h>
#include "buttons.h"

namespace buttons{
	static const pin_size_t ButtonBackLeftPin = 6;
	static const pin_size_t ButtonBackRightPin = 5;
	static const pin_size_t ButtonFrontLeftPin = 4;
	static const pin_size_t ButtonFrontRightPin = 3;

	void init(){
		pinMode(ButtonBackLeftPin, INPUT_PULLUP);
		pinMode(ButtonBackRightPin, INPUT_PULLUP);
		pinMode(ButtonFrontLeftPin, INPUT_PULLUP);
		pinMode(ButtonFrontRightPin, INPUT_PULLUP);
	}

	void setBackLeftPressedCallback(Callback callback){
		attachInterrupt(digitalPinToInterrupt(ButtonBackLeftPin), callback, FALLING);
	}

	void setBackRightPressedCallback(Callback callback){
		attachInterrupt(digitalPinToInterrupt(ButtonBackRightPin), callback, FALLING);
	}

	void setFrontLeftPressedCallback(Callback callback){
		attachInterrupt(digitalPinToInterrupt(ButtonFrontLeftPin), callback, FALLING);
	}

	void setFrontRightPressedCallback(Callback callback){
		attachInterrupt(digitalPinToInterrupt(ButtonFrontRightPin), callback, FALLING);
	}

	bool backLeftPressed(){
		return digitalRead(ButtonBackLeftPin) == LOW;
	}

	bool backRightPressed(){
		return digitalRead(ButtonBackRightPin) == LOW;
	}
}
