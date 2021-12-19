#include <Arduino.h>
#include "buttons.h"

static const pin_size_t ButtonLeftPin = 6;
static const pin_size_t ButtonRightPin = 5;

void initButtons(void){
	pinMode(ButtonLeftPin, INPUT_PULLUP);
	pinMode(ButtonRightPin, INPUT_PULLUP);
}

bool buttonLeftPressed(void){
	return digitalRead(ButtonLeftPin) == LOW;
}

bool buttonRightPressed(void){
	return digitalRead(ButtonRightPin) == LOW;
}
