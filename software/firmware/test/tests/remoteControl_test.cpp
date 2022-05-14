#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "lowPower.h"
#include "remoteControl.h"
#include "irRemoteHandler.h"
#include "turnTable.h"
#include "buttons.h"

static void lowPower_disableSensors_mock(){
	mock().actualCall("lowPower_disableSensors_mock");
}

static void lowPower_sleep_mock(){
	mock().actualCall("lowPower_sleep_mock");
}

static void irRemoteHandler_init_mock(){
	mock().actualCall("irRemoteHandler_init_mock");
}

static void irRemoteHandler_send_mock(irRemoteHandler::Command command){
	mock().actualCall("irRemoteHandler_send_mock")
		.withIntParameter("command", (int)command);
}

static void turnTable_init_mock(){
	mock().actualCall("turnTable_init_mock");
}

static void turnTable_tick_mock(){
	mock().actualCall("turnTable_tick_mock");
}

static void turnTable_sendCommand_mock(turnTable::Command command){
	mock().actualCall("turnTable_sendCommand_mock")
		.withIntParameter("command", (int)command);
}

static bool turnTable_isConnected_mock(){
	mock().actualCall("turnTable_isConnected_mock");
	return mock().boolReturnValue();
}

static void turnTable_disconnect_mock(){
	mock().actualCall("turnTable_disconnect_mock");
}

static void buttons_init_mock(){
	mock().actualCall("buttons_init_mock");
}

static void buttons_tick_mock(){
	mock().actualCall("buttons_tick_mock");
}

static buttons::Buttons buttons_getPressedEvent_mock(){
	mock().actualCall("buttons_getPressedEvent_mock");
	return (buttons::Buttons)mock().returnIntValueOrDefault((int)buttons::Buttons::None);
}

static void buttons_clearPressedEvent_mock(){
	mock().actualCall("buttons_clearPressedEvent_mock");
}

static bool buttons_backLeftPressed_mock(){
	mock().actualCall("buttons_backLeftPressed_mock");
	return mock().boolReturnValue();
}

static bool buttons_backRightPressed_mock(){
	mock().actualCall("buttons_backRightPressed_mock");
	return mock().boolReturnValue();
}

static unsigned long buttons_getLastPressedMillis_mock(){
	mock().actualCall("buttons_getLastPressedMillis_mock");
	return mock().returnUnsignedLongIntValueOrDefault(0);
}

TEST_GROUP(remoteControl_test){
	void setup(void){
		UT_PTR_SET(lowPower::disableSensors, lowPower_disableSensors_mock);
		UT_PTR_SET(lowPower::sleep, lowPower_sleep_mock);

		UT_PTR_SET(irRemoteHandler::init, irRemoteHandler_init_mock);
		UT_PTR_SET(turnTable::init, turnTable_init_mock);
		UT_PTR_SET(buttons::init, buttons_init_mock);

		UT_PTR_SET(irRemoteHandler::send, irRemoteHandler_send_mock);
		UT_PTR_SET(turnTable::tick, turnTable_tick_mock);
		UT_PTR_SET(turnTable::sendCommand, turnTable_sendCommand_mock);
		UT_PTR_SET(turnTable::isConnected, turnTable_isConnected_mock);
		UT_PTR_SET(turnTable::disconnect, turnTable_disconnect_mock);

		UT_PTR_SET(buttons::tick, buttons_tick_mock);
		UT_PTR_SET(buttons::getPressedEvent, buttons_getPressedEvent_mock);
		UT_PTR_SET(buttons::clearPressedEvent, buttons_clearPressedEvent_mock);
		UT_PTR_SET(buttons::backLeftPressed, buttons_backLeftPressed_mock);
		UT_PTR_SET(buttons::backRightPressed, buttons_backRightPressed_mock);
		UT_PTR_SET(buttons::getLastPressedMillis, buttons_getLastPressedMillis_mock);
	}

	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};

TEST(remoteControl_test, setup){
	mock().expectOneCall("lowPower_disableSensors_mock");
	mock().expectOneCall("irRemoteHandler_init_mock");
	mock().expectOneCall("turnTable_init_mock");
	mock().expectOneCall("buttons_init_mock");

	remoteControl::setup();
}

TEST(remoteControl_test, turnTable_tick_tickFunctions){
	mock().expectOneCall("turnTable_tick_mock");
	mock().expectOneCall("buttons_tick_mock");
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, turnTable_tick_noSleep){
	mock().expectOneCall("millis")
		.andReturnValue(10000);
	mock().expectOneCall("buttons_getLastPressedMillis_mock")
		.andReturnValue(0);
	mock().expectNoCall("turnTable_disconnect_mock");
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, turnTable_tick_sleep){
	mock().strictOrder();
	mock().expectOneCall("millis")
		.andReturnValue(10003);
	mock().expectOneCall("buttons_getLastPressedMillis_mock")
		.andReturnValue(2);

	mock().expectOneCall("turnTable_disconnect_mock");
	mock().expectOneCall("delay")
		.withParameter("ms", 1);
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", 25)
		.withParameter("val", 0);
	mock().expectOneCall("lowPower_sleep_mock");
	mock().expectOneCall("digitalWrite")
		.withParameter("pin", 25)
		.withParameter("val", 1);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, Buttons_BackLeft){
	mock().strictOrder();
	mock().expectOneCall("buttons_getPressedEvent_mock")
		.andReturnValue((int)buttons::Buttons::BackLeft);
	mock().expectOneCall("buttons_backLeftPressed_mock")
		.andReturnValue(true);
	mock().expectOneCall("turnTable_isConnected_mock")
		.andReturnValue(true);
	mock().expectOneCall("buttons_clearPressedEvent_mock");
	mock().expectOneCall("turnTable_sendCommand_mock")
		.withIntParameter("command", (int)turnTable::Command::TurnCounterClockWise);
	mock().expectOneCall("buttons_backLeftPressed_mock")
		.andReturnValue(false);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, Buttons_BackRight){
	mock().strictOrder();
	mock().expectOneCall("buttons_getPressedEvent_mock")
		.andReturnValue((int)buttons::Buttons::BackRight);
	mock().expectOneCall("buttons_backRightPressed_mock")
		.andReturnValue(true);
	mock().expectOneCall("turnTable_isConnected_mock")
		.andReturnValue(true);
	mock().expectOneCall("buttons_clearPressedEvent_mock");
	mock().expectOneCall("turnTable_sendCommand_mock")
		.withIntParameter("command", (int)turnTable::Command::TurnClockWise);
	mock().expectOneCall("buttons_backRightPressed_mock")
		.andReturnValue(false);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, Buttons_FrontLeft){
	mock().strictOrder();
	mock().expectOneCall("buttons_getPressedEvent_mock")
		.andReturnValue((int)buttons::Buttons::FrontLeft);
	mock().expectOneCall("buttons_clearPressedEvent_mock");
	mock().expectOneCall("irRemoteHandler_send_mock")
		.withIntParameter("command", (int)irRemoteHandler::Command::HiFi_ToggleStandby);
	mock().expectOneCall("delay")
		.withParameter("ms", 100);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}

TEST(remoteControl_test, Buttons_FrontRight){
	mock().strictOrder();
	mock().expectOneCall("buttons_getPressedEvent_mock")
		.andReturnValue((int)buttons::Buttons::FrontRight);
	mock().expectOneCall("buttons_clearPressedEvent_mock");
	mock().expectOneCall("irRemoteHandler_send_mock")
		.withIntParameter("command", (int)irRemoteHandler::Command::TV_ToggleStandby);
	mock().expectOneCall("delay")
		.withParameter("ms", 100);
	mock().ignoreOtherCalls();

	remoteControl::tick();
}
