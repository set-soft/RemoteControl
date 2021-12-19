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
	initButtons();
}

TEST(buttons_test, buttonLeftPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 6)
		.andReturnValue(1);
	CHECK_FALSE(buttonLeftPressed());
}

TEST(buttons_test, buttonLeftPressed_true){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 6)
		.andReturnValue(0);
	CHECK(buttonLeftPressed());
}

TEST(buttons_test, buttonRightPressed_false){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 5)
		.andReturnValue(1);
	CHECK_FALSE(buttonRightPressed());
}

TEST(buttons_test, buttonRightPressed_true){
	mock().expectOneCall("digitalRead")
		.withParameter("pin", 5)
		.andReturnValue(0);
	CHECK(buttonRightPressed());
}
