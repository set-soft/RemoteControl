#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "buttons.h"

typedef void(*InterruptFunction)();

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

static InterruptFunction getPinInterruptFunction(uint8_t pinNumber){
	const char* DataName = ("func"+std::to_string(pinNumber)).c_str();
	return mock().getData(DataName).getFunctionPointerValue();
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

TEST(buttons_test, tick_noEvent){
	buttons::tick();
	mock().expectNoCall("millis");
}

TEST(buttons_test, lastPressedTime){
	mock().ignoreOtherCalls();
	buttons::init();

	for(uint8_t n=0; n<sizeof(Pins)/sizeof(Pins[0]); n++){
		InterruptFunction func = getPinInterruptFunction(Pins[n]);

		func();
		mock().expectOneCall("millis")
			.andReturnValue(n);
		buttons::tick();
		CHECK_EQUAL(n, buttons::getLastPressedMillis());
	}
}

TEST(buttons_test, event){
	static const buttons::Buttons Buttons[] = {	buttons::Buttons::BackLeft,
												buttons::Buttons::BackRight,
												buttons::Buttons::FrontLeft,
												buttons::Buttons::FrontRight};

	mock().ignoreOtherCalls();
	buttons::init();

	for(uint8_t n=0; n<sizeof(Pins)/sizeof(Pins[0]); n++){
		InterruptFunction func = getPinInterruptFunction(Pins[n]);

		CHECK(buttons::Buttons::None == buttons::getPressedEvent());
		func();
		CHECK(buttons::Buttons::None == buttons::getPressedEvent());
		buttons::tick();
		CHECK(Buttons[n] == buttons::getPressedEvent());
		buttons::clearPressedEvent();
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
	const unsigned long Time = 253;
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 6)
		.andReturnValue(0);
	mock().expectOneCall("millis")
		.andReturnValue(Time);

	CHECK(buttons::backLeftPressed());

	CHECK_EQUAL(Time, buttons::getLastPressedMillis());
}

TEST(buttons_test, buttonBackRightPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 5)
		.andReturnValue(1);
	CHECK_FALSE(buttons::backRightPressed());
}

TEST(buttons_test, buttonBackRightPressed_true){
	const unsigned long Time = 25;
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 5)
		.andReturnValue(0);
	mock().expectOneCall("millis")
		.andReturnValue(Time);

	CHECK(buttons::backRightPressed());

	CHECK_EQUAL(Time, buttons::getLastPressedMillis());
}
