#include "Philips_RC5_IrRemoteProtocol.h"
#include <Arduino.h> //TODO: try to remove this include

namespace Philips_RC5_IrRemote{
	Protocol::Protocol(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		this->infraRed_on = infraRed_on;
		this->infraRed_off = infraRed_off;
		this->waitUs = waitUs;
	}
	
	void Protocol::send(Address address, Command command){
		noInterrupts(); //disable interrupts makes the timing better
		sendStartBits();
		sendToggleBit();
		sendAddress(address);
		sendCommand(command);
		interrupts();
	}

	void Protocol::sendStartBits(){
		this->sendHighBit();
		this->sendHighBit();
	}

	void Protocol::sendToggleBit(){
		if(this->toggleBit){
			sendHighBit();
			toggleBit = false;
		}
		else{
			sendLowBit();
			toggleBit = true;
		}
	}

	void Protocol::sendAddress(Address address){
		sendLowestBits((uint8_t)address, 5);
	}

	void Protocol::sendCommand(Command command){
		sendLowestBits((uint8_t)command, 6);
	}

	void Protocol::sendLowestBits(uint8_t data, uint8_t nrOfBits){
		const uint8_t Mask = 0x01 << (nrOfBits-1);
		for(uint8_t n=0; n<nrOfBits; n++){
			if(data & Mask){
				sendHighBit();
			}
			else{
				sendLowBit();
			}
			data <<= 1;
		}
	}

	void Protocol::sendHighBit(){
		this->waitUs(889);
		sendCarrierNTimes(32);
	}

	void Protocol::sendLowBit(){
		sendCarrierNTimes(32);
		this->waitUs(889);
	}

	void Protocol::sendCarrierNTimes(uint16_t periods){
		for(uint16_t n=0; n < periods; n++){
			this->infraRed_on();
			this->waitUs(CarrierPeriodHalf_us);
			this->infraRed_off();
			this->waitUs(CarrierPeriodHalf_us);
		}
	}
}
