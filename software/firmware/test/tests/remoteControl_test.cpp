#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "remoteControl.h"
#include "irRemoteHandler.h"
#include "turnTable.h"
#include "buttons.h"

static void irRemoteHandler_init_mock(){
	mock().actualCall("irRemoteHandler_init_mock");
}

static void turnTable_init_mock(){
	mock().actualCall("turnTable_init_mock");
}

static void buttons_init_mock(){
	mock().actualCall("buttons_init_mock");
}

static void irRemoteHandler_send_mock(irRemoteHandler::Command command){
	mock().actualCall("irRemoteHandler_send_mock")
		.withIntParameter("command", (int)command);
}

static void turnTable_tick_mock(){
	mock().actualCall("turnTable_tick_mock");
}

static void turnTable_sendCommand_mock(turnTable::Command command){
	mock().actualCall("turnTable_sendCommand_mock")
		.withIntParameter("command", (int)command);
}

static buttons::Buttons buttons_getPressedEvent_mock(){
	mock().actualCall("buttons_getPressedEvent_mock");
	return (buttons::Buttons)mock().returnIntValueOrDefault((int)buttons::Buttons::None);
}

static bool buttons_backLeftPressed_mock(){
	mock().actualCall("buttons_backLeftPressed_mock");
	return mock().boolReturnValue();
}

static bool buttons_backRightPressed_mock(){
	mock().actualCall("buttons_backRightPressed_mock");
	return mock().boolReturnValue();
}

TEST_GROUP(remoteControl_test){
	void setup(void){
		UT_PTR_SET(irRemoteHandler::init, irRemoteHandler_init_mock);
		UT_PTR_SET(turnTable::init, turnTable_init_mock);
		UT_PTR_SET(buttons::init, buttons_init_mock);

		UT_PTR_SET(irRemoteHandler::send, irRemoteHandler_send_mock);
		UT_PTR_SET(turnTable::tick, turnTable_tick_mock);
		UT_PTR_SET(turnTable::sendCommand, turnTable_sendCommand_mock);
		UT_PTR_SET(buttons::getPressedEvent, buttons_getPressedEvent_mock);
		UT_PTR_SET(buttons::backLeftPressed, buttons_backLeftPressed_mock);
		UT_PTR_SET(buttons::backRightPressed, buttons_backRightPressed_mock);
	}

	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};

TEST(remoteControl_test, setup){
	mock().expectOneCall("irRemoteHandler_init_mock");
	mock().expectOneCall("turnTable_init_mock");
	mock().expectOneCall("buttons_init_mock");

	remoteControl::setup();
}

TEST(remoteControl_test, turnTable_tick){
	mock().expectOneCall("turnTable_tick_mock");
	mock().ignoreOtherCalls();
	remoteControl::tick();
}

TEST(remoteControl_test, Buttons_BackLeft){
	mock().expectOneCall("buttons_getPressedEvent_mock")
		.andReturnValue((int)buttons::Buttons::BackLeft);
	mock().expectOneCall("buttons_backLeftPressed_mock")
		.andReturnValue(true);
	mock().expectOneCall("turnTable_sendCommand_mock")
		.withIntParameter("command", (int)turnTable::Command::TurnCounterClockWise);
	mock().expectOneCall("buttons_backLeftPressed_mock")
		.andReturnValue(false);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, Buttons_BackRight){
	mock().expectOneCall("buttons_getPressedEvent_mock")
		.andReturnValue((int)buttons::Buttons::BackRight);
	mock().expectOneCall("buttons_backRightPressed_mock")
		.andReturnValue(true);
	mock().expectOneCall("turnTable_sendCommand_mock")
		.withIntParameter("command", (int)turnTable::Command::TurnClockWise);
	mock().expectOneCall("buttons_backRightPressed_mock")
		.andReturnValue(false);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, Buttons_FrontLeft){
	mock().expectOneCall("buttons_getPressedEvent_mock")
		.andReturnValue((int)buttons::Buttons::FrontLeft);
	mock().expectOneCall("irRemoteHandler_send_mock")
		.withIntParameter("command", (int)irRemoteHandler::Command::HiFi_ToggleStandby);
	mock().expectOneCall("delay")
		.withParameter("ms", 100);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, Buttons_FrontRight){
	mock().expectOneCall("buttons_getPressedEvent_mock")
		.andReturnValue((int)buttons::Buttons::FrontRight);
	mock().expectOneCall("irRemoteHandler_send_mock")
		.withIntParameter("command", (int)irRemoteHandler::Command::TV_ToggleStandby);
	mock().expectOneCall("delay")
		.withParameter("ms", 100);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}
