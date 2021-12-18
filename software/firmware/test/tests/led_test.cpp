#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "led.h"

TEST_GROUP(led_test){
	void setup(void){}
	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};

TEST(led_test, init){
	mock().expectOneCall("pinMode")
		.withParameter("pin_size_t", 13)
		.withParameter("PinMode", 1);
	initLed();
}

TEST(led_test, on){
	mock().expectOneCall("digitalWrite")
		.withParameter("pin_size_t", 13)
		.withParameter("PinStatus", 1);
	setLedOn();
}

TEST(led_test, off){
	mock().expectOneCall("digitalWrite")
		.withParameter("pin_size_t", 13)
		.withParameter("PinStatus", 0);
	setLedOff();
}
