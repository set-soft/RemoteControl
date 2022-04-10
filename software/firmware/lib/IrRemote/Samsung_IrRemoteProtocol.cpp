#include "Samsung_IrRemoteProtocol.h"
#include "IrRemoteRaw.h"
#include <Arduino.h> //TODO: try to remove this include

namespace Samsung_IrRemote{
	static const unsigned int CarrierPeriodHalf_us = 13;
	static InfraRed_on infraRed_on;
	static InfraRed_off infraRed_off;
	static WaitMicroseconds waitUs;
	static IrRemoteRaw::Configuration irRemoteRawConfig;

	static void waitCarrierHalfPeriod();
	static void sendStartBit();
	static void sendByte(uint8_t data);
	static void sendHighBit();
	static void sendLowBit();
	static void sendStopBit();

	void init(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		Samsung_IrRemote::infraRed_on = infraRed_on;
		Samsung_IrRemote::infraRed_off = infraRed_off;
		Samsung_IrRemote::waitUs = waitUs;
		irRemoteRawConfig.infraRed_on = infraRed_on;
		irRemoteRawConfig.infraRed_off = infraRed_off;
		irRemoteRawConfig.waitCarrierHalfPeriod = waitCarrierHalfPeriod;
	}

	static void waitCarrierHalfPeriod(){
		waitUs(CarrierPeriodHalf_us);
	}
	
	void send(const uint16_t Address, const uint8_t Data){
		noInterrupts(); //disable interrupts makes the timing better
		sendStartBit();
		sendByte(Address >> 8);
		sendByte(Address & 0x00FF);
		sendByte(Data);
		sendByte(~Data);
		sendStopBit();
		interrupts();
	}

	static void sendStartBit(){
		const unsigned int StartBitHalf_us = 4500;
		const unsigned int CarrierPeriods = StartBitHalf_us / (2*CarrierPeriodHalf_us);
		IrRemoteRaw::sendCarrierNTimes(CarrierPeriods, irRemoteRawConfig);
		waitUs(StartBitHalf_us);
	}

	static void sendByte(uint8_t data){
		for(uint8_t n=0; n<8; n++){
			if(data & 0x80){
				sendHighBit();
			}
			else{
				sendLowBit();
			}
			data <<= 1;
		}
	}

	static void sendHighBit(){
		IrRemoteRaw::sendCarrierNTimes(21, irRemoteRawConfig);
		waitUs(1690);
	}

	static void sendLowBit(){
		IrRemoteRaw::sendCarrierNTimes(21, irRemoteRawConfig);
		waitUs(560);
	}

	static void sendStopBit(){
		sendHighBit(); //A low bit could work as well.
	}
}