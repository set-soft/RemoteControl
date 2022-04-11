#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Philips_RC5_IrRemoteProtocol.h"
#include "IrRemoteRaw.h"

static void infraRed_on_mock(){
	mock().actualCall("infraRed_on_mock");
}

static void infraRed_off_mock(){
	mock().actualCall("infraRed_off_mock");
}

static void waitUs_mock(unsigned int microSeconds){
	mock().actualCall("waitUs_mock")
		.withParameter("microSeconds", microSeconds);
}

static void sendCarrierNTimes_mock(uint16_t periods, IrRemoteRaw::Configuration configuration){
	mock().actualCall("sendCarrierNTimes_mock")
		.withParameter("periods", periods);

	CHECK_EQUAL(infraRed_on_mock, configuration.infraRed_on);
	CHECK_EQUAL(infraRed_off_mock, configuration.infraRed_off);
	configuration.waitCarrierHalfPeriod();
}


TEST_GROUP(Philips_RC5_IrRemoteProtocol_test){
	void setup(void){
		UT_PTR_SET(IrRemoteRaw::sendCarrierNTimes, sendCarrierNTimes_mock);
	}

	void teardown(void){
    	mock().checkExpectations();
		mock().clear();
	}
};


static void expect_sendCarrierNTimes(uint16_t periods){
	mock().expectOneCall("sendCarrierNTimes_mock")
		.withParameter("periods", periods);
	mock().expectOneCall("waitUs_mock")
		.withParameter("microSeconds", 15);
}

static void expect_sendHighBit(){
	mock().expectOneCall("waitUs_mock")
		.withParameter("microSeconds", 889);
	expect_sendCarrierNTimes(32);
}

static void expect_sendLowBit(){
	expect_sendCarrierNTimes(32);
	mock().expectOneCall("waitUs_mock")
		.withParameter("microSeconds", 889);
}

static void expect_sendStartBits(){
	expect_sendHighBit();
	expect_sendHighBit();
}

static void expect_sendToggleBit_Low(){
	expect_sendLowBit();
}

static void expect_sendToggleBit_High(){
	expect_sendHighBit();
}

static void expect_sendLowestBits(uint8_t data, uint8_t nrOfBits){
	const uint8_t Mask = 0x01 << (nrOfBits-1);
	for(uint8_t n=0; n<nrOfBits; n++){
		if(data & Mask){
			expect_sendHighBit();
		}
		else{
			expect_sendLowBit();
		}
		data <<= 1;
	}
}

static void expect_sendAddress(Philips_RC5_IrRemote::Address address){
	expect_sendLowestBits((uint8_t) address, 5);
}

static void expect_sendCommand(Philips_RC5_IrRemote::Command command){
	expect_sendLowestBits((uint8_t) command, 6);
}

static void expect_sendCalls(Philips_RC5_IrRemote::Address address, Philips_RC5_IrRemote::Command command){
	static bool toggleBit = false;

	mock().strictOrder();
	mock().expectOneCall("noInterrupts"); //TODO: remove
	expect_sendStartBits();
	if(toggleBit){
		expect_sendToggleBit_High();
		toggleBit = false;
	}
	else{
		expect_sendToggleBit_Low();
		toggleBit = true;
	}
	expect_sendAddress(address);
	expect_sendCommand(command);
	mock().expectOneCall("interrupts"); //TODO: remove
}


TEST(Philips_RC5_IrRemoteProtocol_test, send){
	const Philips_RC5_IrRemote::Address Address = Philips_RC5_IrRemote::Address::Recorder1;
	const Philips_RC5_IrRemote::Command Command = Philips_RC5_IrRemote::Command::Key7; 

	expect_sendCalls(Address, Command);

	Philips_RC5_IrRemote::init(infraRed_on_mock, infraRed_off_mock, waitUs_mock);
	Philips_RC5_IrRemote::send(Address, Command);
}

TEST(Philips_RC5_IrRemoteProtocol_test, toggleBit){
	const Philips_RC5_IrRemote::Address Address = Philips_RC5_IrRemote::Address::TV1;
	const Philips_RC5_IrRemote::Command Command = Philips_RC5_IrRemote::Command::Standby; 

	expect_sendCalls(Address, Command);
	expect_sendCalls(Address, Command);
	expect_sendCalls(Address, Command);
	expect_sendCalls(Address, Command);

	Philips_RC5_IrRemote::init(infraRed_on_mock, infraRed_off_mock, waitUs_mock);
	Philips_RC5_IrRemote::send(Address, Command);
	Philips_RC5_IrRemote::send(Address, Command);
	Philips_RC5_IrRemote::send(Address, Command);
	Philips_RC5_IrRemote::send(Address, Command);
}
