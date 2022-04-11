#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "FINLUX__32FLE845_Eco__IrRemote.h"
#include "Philips_RC5_IrRemoteProtocol.h"

TEST_GROUP(FINLUX__32FLE845_Eco__IrRemote_test){
	void setup(void){}
	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};


static void Philips_RC5_IrRemote_init_mock(	const Philips_RC5_IrRemote::InfraRed_on infraRed_on,
											const Philips_RC5_IrRemote::InfraRed_off infraRed_off,
											const Philips_RC5_IrRemote::WaitMicroseconds waitUs){
	mock().actualCall("Philips_RC5_IrRemote_init_mock")
		.withFunctionPointerParameter("infraRed_on", infraRed_on)
		.withFunctionPointerParameter("infraRed_off", infraRed_off)
		.withFunctionPointerParameter("waitUs", (void(*)())waitUs);
}

static void Philips_RC5_IrRemote_send_mock(	Philips_RC5_IrRemote::Address address,
											Philips_RC5_IrRemote::Command command){
	mock().actualCall("Philips_RC5_IrRemote_send_mock")
		.withIntParameter("address", (int)address)
		.withIntParameter("command", (int)command);
}

static void infraRed_on_stub(){}
static void infraRed_off_stub(){}
static void waitUs_stub(unsigned int microseconds){}

TEST(FINLUX__32FLE845_Eco__IrRemote_test, init){
	UT_PTR_SET(Philips_RC5_IrRemote::init, Philips_RC5_IrRemote_init_mock);
	mock().expectOneCall("Philips_RC5_IrRemote_init_mock")
		.withFunctionPointerParameter("infraRed_on", infraRed_on_stub)
		.withFunctionPointerParameter("infraRed_off", infraRed_off_stub)
		.withFunctionPointerParameter("waitUs", (void(*)())waitUs_stub);

	FINLUX__32FLE845_Eco::init(infraRed_on_stub, infraRed_off_stub, waitUs_stub);
}

TEST(FINLUX__32FLE845_Eco__IrRemote_test, ToggleStandby){
	UT_PTR_SET(Philips_RC5_IrRemote::send, Philips_RC5_IrRemote_send_mock);
	mock().expectOneCall("Philips_RC5_IrRemote_send_mock")
		.withIntParameter("address", (int)Philips_RC5_IrRemote::Address::TV1)
		.withIntParameter("command", (int)Philips_RC5_IrRemote::Command::Standby);

	FINLUX__32FLE845_Eco::send(FINLUX__32FLE845_Eco::Command::ToggleStandby);
}

TEST(FINLUX__32FLE845_Eco__IrRemote_test, invalidCommand){
	UT_PTR_SET(Philips_RC5_IrRemote::send, Philips_RC5_IrRemote_send_mock);
	mock().expectNoCall("Philips_RC5_IrRemote_send_mock");
	
	using namespace FINLUX__32FLE845_Eco;
	Command invalidCommand = (Command)((uint8_t)Command::ToggleStandby+1);
	send(invalidCommand);
}
