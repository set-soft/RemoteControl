#include "Philips_RC5_IrRemoteProtocol.h"
#include <Arduino.h> //TODO: try to remove this include

namespace Philips_RC5_IrRemote{
	static const unsigned int CarrierPeriodHalf_us = 15;
	static bool toggleBit;
	static InfraRed_on infraRed_on;
	static InfraRed_off infraRed_off;
	static WaitMicroseconds waitUs;
	static IrRemoteRaw::Configuration irRemoteRawConfig;

	static void waitCarrierHalfPeriod();
	static void sendStartBits();
	static void sendToggleBit();
	static void sendAddress(Address address);
	static void sendCommand(Command command);
	static void sendLowestBits(uint8_t data, uint8_t nrOfBits);
	static void sendHighBit();
	static void sendLowBit();

	void init(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		Philips_RC5_IrRemote::infraRed_on = infraRed_on;
		Philips_RC5_IrRemote::infraRed_off = infraRed_off;
		Philips_RC5_IrRemote::waitUs = waitUs;
		irRemoteRawConfig.infraRed_on = infraRed_on;
		irRemoteRawConfig.infraRed_off = infraRed_off;
		irRemoteRawConfig.waitCarrierHalfPeriod = waitCarrierHalfPeriod;
		toggleBit = false;
	}

	static void waitCarrierHalfPeriod(){
		waitUs(CarrierPeriodHalf_us);
	}
	
	void send(Address address, Command command){
		noInterrupts(); //disable interrupts makes the timing better
		sendStartBits();
		sendToggleBit();
		sendAddress(address);
		sendCommand(command);
		interrupts();
	}

	static void sendStartBits(){
		sendHighBit();
		sendHighBit();
	}

	static void sendToggleBit(){
		if(toggleBit){
			sendHighBit();
			toggleBit = false;
		}
		else{
			sendLowBit();
			toggleBit = true;
		}
	}

	static void sendAddress(Address address){
		sendLowestBits((uint8_t)address, 5);
	}

	static void sendCommand(Command command){
		sendLowestBits((uint8_t)command, 6);
	}

	static void sendLowestBits(uint8_t data, uint8_t nrOfBits){
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

	static void sendHighBit(){
		waitUs(889);
		IrRemoteRaw::sendCarrierNTimes(32, irRemoteRawConfig);
	}

	static void sendLowBit(){
		IrRemoteRaw::sendCarrierNTimes(32, irRemoteRawConfig);
		waitUs(889);
	}
}
