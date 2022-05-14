#include "remoteControl.h"
#include <Arduino.h>

// This file is not unit-tested:
// It contains only glue-code and is not really testable.

int main(){
	init();
	initVariant();

	setup();

	for(;;){
		loop();
	}

	return 0;
}

void setup(){
	remoteControl::setup();
}

void loop(){
	remoteControl::tick();
}
