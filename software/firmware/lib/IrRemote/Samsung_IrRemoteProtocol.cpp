#include "Samsung_IrRemoteProtocol.h"
#include <Arduino.h> //TODO: try to remove this include

namespace Samsung_IrRemote{
	Protocol::Protocol(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		this->infraRed_on = infraRed_on;
		this->infraRed_off = infraRed_off;
		this->waitUs = waitUs;
	}
	
	void Protocol::send(const uint16_t Address, const uint8_t Data){
		noInterrupts(); //disable interrupts makes the timing better
		sendStartBit();
		sendByte(Address >> 8);
		sendByte(Address & 0x00FF);
		sendByte(Data);
		sendByte(~Data);
		sendStopBit();
		interrupts();
	}

	void Protocol::sendStartBit(){
		const unsigned int CarrierPeriods = StartBitHalf_us / (2*CarrierPeriodHalf_us);
		sendCarrierNTimes(CarrierPeriods);
		this->waitUs(StartBitHalf_us);
	}

	void Protocol::sendCarrierNTimes(uint16_t periods){
		for(uint16_t n=0; n < periods; n++){
			this->infraRed_on();
			this->waitUs(CarrierPeriodHalf_us);
			this->infraRed_off();
			this->waitUs(CarrierPeriodHalf_us);
		}
	}

	void Protocol::sendByte(uint8_t data){
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

	void Protocol::sendHighBit(){
		sendCarrierNTimes(21);
		this->waitUs(1690);
	}

	void Protocol::sendLowBit(){
		sendCarrierNTimes(21);
		this->waitUs(560);
	}

	void Protocol::sendStopBit(){
		sendHighBit(); //A low bit could work as well.
	}
}