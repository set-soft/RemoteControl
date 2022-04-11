#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "buttons.h"

static const uint8_t Pins[] = {6, 5, 4, 3};

TEST_GROUP(buttons_test){
	void setup(void){}
	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};


static void expect_pinMode(uint8_t pin){
	mock().expectOneCall("pinMode")
		.withParameter("pin", pin)
		.withParameter("mode", 2);
}

static void expect_attachInterrupt(uint8_t pin){
	mock().expectOneCall("digitalPinToInterrupt")
		.withParameter("pin", pin);
	mock().expectOneCall("attachInterrupt")
		.withParameter("interruptNum", pin)
		.withParameter("mode", 3);
}


TEST(buttons_test, init){
	mock().strictOrder();
	for(uint8_t n=0; n<sizeof(Pins)/sizeof(Pins[0]); n++){
		expect_pinMode(Pins[n]);
	}
	mock().strictOrder();
	for(uint8_t n=0; n<sizeof(Pins)/sizeof(Pins[0]); n++){
		expect_attachInterrupt(Pins[n]);
	}

	buttons::init();
}

TEST(buttons_test, event){
	static const buttons::Buttons Buttons[] = {	buttons::Buttons::BackLeft,
												buttons::Buttons::BackRight,
												buttons::Buttons::FrontLeft,
												buttons::Buttons::FrontRight};

	mock().ignoreOtherCalls();
	buttons::init();

	for(uint8_t n=0; n<sizeof(Pins)/sizeof(Pins[0]); n++){
		const char* DataName = ("func"+std::to_string(Pins[n])).c_str();
		void(*func)() = mock().getData(DataName).getFunctionPointerValue();

		CHECK(buttons::Buttons::None == buttons::getPressedEvent());
		func();
		CHECK(Buttons[n] == buttons::getPressedEvent());
		CHECK(buttons::Buttons::None == buttons::getPressedEvent());
	}
}


TEST(buttons_test, buttonBackLeftPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 6)
		.andReturnValue(1);
	CHECK_FALSE(buttons::backLeftPressed());
}

TEST(buttons_test, buttonBackLeftPressed_true){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 6)
		.andReturnValue(0);
	CHECK(buttons::backLeftPressed());
}

TEST(buttons_test, buttonBackRightPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 5)
		.andReturnValue(1);
	CHECK_FALSE(buttons::backRightPressed());
}

TEST(buttons_test, buttonBackRightPressed_true){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 5)
		.andReturnValue(0);
	CHECK(buttons::backRightPressed());
}
