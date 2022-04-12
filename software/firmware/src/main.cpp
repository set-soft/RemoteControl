#include "remoteControl.h"
#include <Arduino.h>

void setup(void){
	remoteControl::setup();
}

void loop(void){
	remoteControl::tick();
}
