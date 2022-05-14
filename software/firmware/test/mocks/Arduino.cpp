#include "Arduino.h"
#include "CppUTestExt/MockSupport.h"

void init(void){}
void initVariant(void){}

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

unsigned long millis(){
	mock().actualCall("millis");
	return mock().returnUnsignedLongIntValueOrDefault(99);
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
	return pin;
}

void attachInterrupt(pin_size_t interruptNum, voidFuncPtr func, PinStatus mode){
	mock().actualCall("attachInterrupt")
		.withParameter("interruptNum", interruptNum)
		.withParameter("mode", mode);

	const char* DataName = ("func"+std::to_string(interruptNum)).c_str();
	mock().setData(DataName, func);
}
