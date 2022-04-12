#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "MELECTRONIC__MC_MI_1212__IrRemote.h"
#include "Samsung_IrRemoteProtocol.h"

TEST_GROUP(MELECTRONIC__MC_MI_1212__IrRemote_test){
	void setup(void){}
	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};


static void Samsung_IrRemote_init_mock(	const Samsung_IrRemote::InfraRed_on infraRed_on,
										const Samsung_IrRemote::InfraRed_off infraRed_off,
										const Samsung_IrRemote::WaitMicroseconds waitUs){
	mock().actualCall("Samsung_IrRemote_init_mock")
		.withFunctionPointerParameter("infraRed_on", infraRed_on)
		.withFunctionPointerParameter("infraRed_off", infraRed_off)
		.withFunctionPointerParameter("waitUs", (void(*)())waitUs);
}

static void Samsung_IrRemote_send_mock(const uint16_t Address, const uint8_t Data){
	mock().actualCall("Samsung_IrRemote_send_mock")
		.withIntParameter("Address", Address)
		.withIntParameter("Data", Data);
}

static void infraRed_on_stub(){}
static void infraRed_off_stub(){}
static void waitUs_stub(unsigned int microseconds){}

TEST(MELECTRONIC__MC_MI_1212__IrRemote_test, init){
	UT_PTR_SET(Samsung_IrRemote::init, Samsung_IrRemote_init_mock);
	mock().expectOneCall("Samsung_IrRemote_init_mock")
		.withFunctionPointerParameter("infraRed_on", infraRed_on_stub)
		.withFunctionPointerParameter("infraRed_off", infraRed_off_stub)
		.withFunctionPointerParameter("waitUs", (void(*)())waitUs_stub);

	MELECTRONIC__MC_MI_1212::init(infraRed_on_stub, infraRed_off_stub, waitUs_stub);
}

TEST(MELECTRONIC__MC_MI_1212__IrRemote_test, ToggleStandby){
	UT_PTR_SET(Samsung_IrRemote::send, Samsung_IrRemote_send_mock);
	mock().expectOneCall("Samsung_IrRemote_send_mock")
		.withIntParameter("Address", 0x0808)
		.withIntParameter("Data", 0x78);

	MELECTRONIC__MC_MI_1212::send(MELECTRONIC__MC_MI_1212::Command::ToggleStandby);
}

TEST(MELECTRONIC__MC_MI_1212__IrRemote_test, invalidCommand){
	UT_PTR_SET(Samsung_IrRemote::send, Samsung_IrRemote_send_mock);
	mock().expectNoCall("Samsung_IrRemote_send_mock");
	
	using namespace MELECTRONIC__MC_MI_1212;
	Command invalidCommand = (Command)((uint8_t)Command::ToggleStandby+1);
	send(invalidCommand);
}
