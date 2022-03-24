#include <Arduino.h>
#include "buttons.h"

static const pin_size_t ButtonBackLeftPin = 6;
static const pin_size_t ButtonBackRightPin = 5;
static const pin_size_t ButtonFrontLeftPin = 4;
static const pin_size_t ButtonFrontRightPin = 3;

void initButtons(void){
	pinMode(ButtonBackLeftPin, INPUT_PULLUP);
	pinMode(ButtonBackRightPin, INPUT_PULLUP);
	pinMode(ButtonFrontLeftPin, INPUT_PULLUP);
	pinMode(ButtonFrontRightPin, INPUT_PULLUP);
}

bool buttonBackLeftPressed(void){
	return digitalRead(ButtonBackLeftPin) == LOW;
}

bool buttonBackRightPressed(void){
	return digitalRead(ButtonBackRightPin) == LOW;
}

bool buttonFrontLeftPressed(void){
	return digitalRead(ButtonFrontLeftPin) == LOW;
}

bool buttonFrontRightPressed(void){
	return digitalRead(ButtonFrontRightPin) == LOW;
}
