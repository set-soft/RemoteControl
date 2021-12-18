#include "led.h"
#include <Arduino.h>

void initLed(void){
	pinMode(LED_BUILTIN, OUTPUT);
}

void setLedOn(void){
	digitalWrite(LED_BUILTIN, HIGH);	
}

void setLedOff(void){
	digitalWrite(LED_BUILTIN, LOW);
}
