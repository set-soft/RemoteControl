#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "buttons.h"

TEST_GROUP(buttons_test){
	void setup(void){}
	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};

TEST(buttons_test, init){
	mock().expectOneCall("pinMode")
		.withParameter("pin", 5)
		.withParameter("mode", 2);
	mock().expectOneCall("pinMode")
		.withParameter("pin", 6)
		.withParameter("mode", 2);
	mock().expectOneCall("pinMode")
		.withParameter("pin", 3)
		.withParameter("mode", 2);
	mock().expectOneCall("pinMode")
		.withParameter("pin", 4)
		.withParameter("mode", 2);
	initButtons();
}

TEST(buttons_test, buttonBackLeftPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 6)
		.andReturnValue(1);
	CHECK_FALSE(buttonBackLeftPressed());
}

TEST(buttons_test, buttonBackLeftPressed_true){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 6)
		.andReturnValue(0);
	CHECK(buttonBackLeftPressed());
}

TEST(buttons_test, buttonBackRightPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 5)
		.andReturnValue(1);
	CHECK_FALSE(buttonBackRightPressed());
}

TEST(buttons_test, buttonBackRightPressed_true){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 5)
		.andReturnValue(0);
	CHECK(buttonBackRightPressed());
}

TEST(buttons_test, buttonFrontLeftPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 4)
		.andReturnValue(1);
	CHECK_FALSE(buttonFrontLeftPressed());
}

TEST(buttons_test, buttonFrontLeftPressed_true){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 4)
		.andReturnValue(0);
	CHECK(buttonFrontLeftPressed());
}

TEST(buttons_test, buttonFrontRightPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 3)
		.andReturnValue(1);
	CHECK_FALSE(buttonFrontRightPressed());
}

TEST(buttons_test, buttonFrontRightPressed_true){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 3)
		.andReturnValue(0);
	CHECK(buttonFrontRightPressed());
}
