#include "Samsung_IrRemoteProtocol.h"
#include "irRemoteRaw.h"
#include <Arduino.h> //TODO: try to remove this include

namespace Samsung_IrRemote{
	static const unsigned int CarrierPeriodHalf_us = 13;
	static InfraRed_on infraRed_on;
	static InfraRed_off infraRed_off;
	static WaitMicroseconds waitUs;
	static irRemoteRaw::Configuration irRemoteRawConfig;

	static void waitCarrierHalfPeriod();
	static void sendStartBit();
	static void sendByte(uint8_t data);
	static void sendHighBit();
	static void sendLowBit();
	static void sendStopBit();

	static void init_Implementation(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		Samsung_IrRemote::infraRed_on = infraRed_on;
		Samsung_IrRemote::infraRed_off = infraRed_off;
		Samsung_IrRemote::waitUs = waitUs;
		irRemoteRawConfig.infraRed_on = infraRed_on;
		irRemoteRawConfig.infraRed_off = infraRed_off;
		irRemoteRawConfig.waitCarrierHalfPeriod = waitCarrierHalfPeriod;
	}
	void (*init)(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs) = init_Implementation;

	static void waitCarrierHalfPeriod(){
		waitUs(CarrierPeriodHalf_us);
	}
	
	static void send_Implementation(const uint16_t Address, const uint8_t Data){
		noInterrupts(); //disable interrupts makes the timing better
		sendStartBit();
		sendByte(Address >> 8);
		sendByte(Address & 0x00FF);
		sendByte(Data);
		sendByte(~Data);
		sendStopBit();
		interrupts();
	}
	void (*send)(const uint16_t Address, const uint8_t Data) = send_Implementation;

	static void sendStartBit(){
		const unsigned int StartBitHalf_us = 4500;
		const unsigned int CarrierPeriods = StartBitHalf_us / (2*CarrierPeriodHalf_us);
		irRemoteRaw::sendCarrierNTimes(CarrierPeriods, irRemoteRawConfig);
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
		irRemoteRaw::sendCarrierNTimes(21, irRemoteRawConfig);
		waitUs(1690);
	}

	static void sendLowBit(){
		irRemoteRaw::sendCarrierNTimes(21, irRemoteRawConfig);
		waitUs(560);
	}

	static void sendStopBit(){
		sendHighBit(); //A low bit could work as well.
	}
}