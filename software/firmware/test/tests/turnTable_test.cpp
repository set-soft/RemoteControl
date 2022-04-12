#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "turnTable.h"

TEST_GROUP(turnTable_test){
	void setup(void){}
	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};

TEST(turnTable_test, init){
	mock().expectOneCall("BLELocalDevice::begin");
	turnTable::init();
}

//TODO: test tick()

TEST(turnTable_test, TurnClockWise){
	mock().expectOneCall("BLECharacteristic::writeValue")
		.withParameter("value", 0x01);

	using namespace turnTable;
	sendCommand(Command::TurnClockWise);
}

TEST(turnTable_test, TurnCounterClockWise){
	mock().expectOneCall("BLECharacteristic::writeValue")
		.withParameter("value", 0x02);

	using namespace turnTable;
	sendCommand(Command::TurnCounterClockWise);
}

TEST(turnTable_test, sendInvalidCommand){
	mock().expectNoCall("BLECharacteristic::writeValue");

	using namespace turnTable;
	sendCommand((Command)123);
}
