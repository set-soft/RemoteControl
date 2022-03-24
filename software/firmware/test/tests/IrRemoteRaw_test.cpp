#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "IrRemoteRaw.h"

TEST_GROUP(IrRemoteRaw_test){
	void setup(void){}
	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};

static void infraRed_on_mock(){
	mock().actualCall("infraRed_on_mock");
}

static void infraRed_off_mock(){
	mock().actualCall("infraRed_off_mock");
}

static void waitCarrierHalfPeriod_mock(){
	mock().actualCall("waitCarrierHalfPeriod_mock");
}

TEST(IrRemoteRaw_test, sendCarrierNTimes){
	const uint8_t NrOfCarriers = 42;

	mock().strictOrder();
	for(uint8_t n=0; n<NrOfCarriers; n++){
		mock().expectOneCall("infraRed_on_mock");
		mock().expectOneCall("waitCarrierHalfPeriod_mock");
		mock().expectOneCall("infraRed_off_mock");
		mock().expectOneCall("waitCarrierHalfPeriod_mock");
	}

	IrRemoteRaw::IrRemoteRaw* irRemoteRaw = new IrRemoteRaw::IrRemoteRaw(infraRed_on_mock, infraRed_off_mock, waitCarrierHalfPeriod_mock);
	irRemoteRaw->sendCarrierNTimes(NrOfCarriers);
	delete irRemoteRaw;
}

TEST(IrRemoteRaw_test, sendCarrierNTimes_zero){
	mock().expectNoCall("infraRed_on_mock");
	mock().expectNoCall("infraRed_off_mock");
	mock().expectNoCall("waitCarrierHalfPeriod_mock");

	IrRemoteRaw::IrRemoteRaw* irRemoteRaw = new IrRemoteRaw::IrRemoteRaw(infraRed_on_mock, infraRed_off_mock, waitCarrierHalfPeriod_mock);
	irRemoteRaw->sendCarrierNTimes(0);
	delete irRemoteRaw;
}
