#include "Arduino.h"
#include "CppUTestExt/MockSupport.h"

void pinMode(pin_size_t pin, PinMode mode){
	mock().actualCall("pinMode")
		.withParameter("pin", pin)
		.withParameter("mode", mode);
}

void digitalWrite(pin_size_t pin, PinStatus val){
	mock().actualCall("digitalWrite")
		.withParameter("pin", pin)
		.withParameter("val", val);
}

PinStatus digitalRead(pin_size_t pin){
	mock().actualCall("digitalRead")
		.withParameter("pin", pin);
	return (PinStatus)mock().intReturnValue();
}

void delay(unsigned long ms){
	mock().actualCall("delay")
		.withParameter("ms", ms);
}

void interrupts(){
	mock().actualCall("interrupts");
}

void noInterrupts(){
	mock().actualCall("noInterrupts");
}

pin_size_t digitalPinToInterrupt(pin_size_t pin){
	mock().actualCall("digitalPinToInterrupt")
		.withParameter("pin", pin);
	return mock().intReturnValue();
}

void attachInterrupt(pin_size_t interruptNum, voidFuncPtr func, PinStatus mode){
	/*mock().actualCall("attachInterrupt");
		.withParameter("interruptNum", interruptNum)
		.withParameter("func", func)
		.withParameter("mode", mode);*/
}
