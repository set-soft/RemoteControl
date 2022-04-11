#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"
#include "Samsung_IrRemoteProtocol.h"
#include "irRemoteRaw.h"

TEST_GROUP(Samsung_IrRemoteProtocol_test){
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

static void waitUs_mock(unsigned int microSeconds){
	mock().actualCall("waitUs_mock")
		.withParameter("microSeconds", microSeconds);
}

static void sendCarrierNTimes_mock(uint16_t periods, irRemoteRaw::Configuration configuration){
	mock().actualCall("sendCarrierNTimes_mock")
		.withParameter("periods", periods);

	CHECK_EQUAL(infraRed_on_mock, configuration.infraRed_on);
	CHECK_EQUAL(infraRed_off_mock, configuration.infraRed_off);
	configuration.waitCarrierHalfPeriod();
}


static void expect_sendCarrierNTimes(uint16_t periods){
	mock().expectOneCall("sendCarrierNTimes_mock")
		.withParameter("periods", periods);
	mock().expectOneCall("waitUs_mock")
		.withParameter("microSeconds", 13);
}

static void expect_sendHighBit(){
	expect_sendCarrierNTimes(21);
	mock().expectOneCall("waitUs_mock")
		.withParameter("microSeconds", 1690);
}

static void expect_sendLowBit(){
	expect_sendCarrierNTimes(21);
	mock().expectOneCall("waitUs_mock")
		.withParameter("microSeconds", 560);
}

static void expect_sendStartBit(){
	expect_sendCarrierNTimes(173);
	mock().expectOneCall("waitUs_mock")
		.withParameter("microSeconds", 4500);
}

static void expect_sendStopBit(){
	expect_sendHighBit();
}

static void expect_sendByte(uint8_t data){
	for(uint8_t n=0; n<8; n++){
		if(data & 0x80){
			expect_sendHighBit();
		}
		else{
			expect_sendLowBit();
		}
		data <<= 1;
	}
}


TEST(Samsung_IrRemoteProtocol_test, send){
	const uint16_t Address = 0x1234;
	const uint8_t Data = 0xAB; 

	UT_PTR_SET(irRemoteRaw::sendCarrierNTimes, sendCarrierNTimes_mock);
	mock().strictOrder();
	mock().expectOneCall("noInterrupts"); //TODO: remove
	expect_sendStartBit();
	expect_sendByte(Address >> 8);
	expect_sendByte(Address & 0x00FF);
	expect_sendByte(Data);
	expect_sendByte((uint8_t)(~Data));
	expect_sendStopBit();
	mock().expectOneCall("interrupts"); //TODO: remove

	Samsung_IrRemote::init(infraRed_on_mock, infraRed_off_mock, waitUs_mock);
	Samsung_IrRemote::send(Address, Data);
}
