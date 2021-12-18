#include "Arduino.h"
#include "CppUTestExt/MockSupport.h"

void pinMode(pin_size_t pin, PinMode mode){
	mock().actualCall("pinMode")
		.withParameter("pin_size_t", pin)
		.withParameter("PinMode", mode);
}

void digitalWrite(pin_size_t pin, PinStatus val){
	mock().actualCall("digitalWrite")
		.withParameter("pin_size_t", pin)
		.withParameter("PinStatus", val);
}

PinStatus digitalRead(pin_size_t pin){return LOW;}
