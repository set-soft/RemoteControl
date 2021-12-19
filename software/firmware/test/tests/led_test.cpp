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
		.withParameter("pin", 13)
		.withParameter("mode", 1);
	initLed();
}

TEST(led_test, on){
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", 13)
		.withParameter("val", 1);
	setLedOn();
}

TEST(led_test, off){
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", 13)
		.withParameter("val", 0);
	setLedOff();
}
