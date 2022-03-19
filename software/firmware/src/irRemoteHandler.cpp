#include "irRemoteHandler.h"
#include "MELECTRONIC__MC_MI_1212__IrRemote.h"

#include <Arduino.h>

namespace irRemoteHandler{
	static MELECTRONIC__MC_MI_1212::IrRemote* irRemote;

	static void infraRed_on();
	static void infraRed_off();
	static void waitUs(unsigned int microSeconds);

	static const pin_size_t IrPin = 9;

	void init(){
		irRemote = new MELECTRONIC__MC_MI_1212::IrRemote(infraRed_on, infraRed_off, waitUs);
		pinMode(IrPin, OUTPUT);
	}
	
	void send(){
		irRemote->send(MELECTRONIC__MC_MI_1212::Command::ToggleOnOff);
	}

	static void infraRed_on(){
		digitalWrite(IrPin, HIGH);
	}

	static void infraRed_off(){
		digitalWrite(IrPin, LOW);
	}

	static void waitUs(unsigned int microSeconds){
		//The microsecond must be more accurate than delayMicroseconds is.
		//This is a bit hacky but more accurate.
		for(uint16_t n = 0; n < microSeconds; n++){
			volatile uint16_t i;
			for(i=0; i<4; i++){
			}
		}
	}
}
