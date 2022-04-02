#include "irRemoteHandler.h"
#include "MELECTRONIC__MC_MI_1212__IrRemote.h"
#include "FINLUX__32FLE845_Eco__IrRemote.h"

#include <Arduino.h>

namespace irRemoteHandler{
	static MELECTRONIC__MC_MI_1212::IrRemote* hifi_irRemote;
	static FINLUX__32FLE845_Eco::IrRemote* tv_irRemote;
	static const pin_size_t IrPin = 9;

	static void infraRed_on();
	static void infraRed_off();
	static void waitUs(unsigned int microSeconds);

	void init(){
		hifi_irRemote = new MELECTRONIC__MC_MI_1212::IrRemote(infraRed_on, infraRed_off, waitUs);
		tv_irRemote = new FINLUX__32FLE845_Eco::IrRemote(infraRed_on, infraRed_off, waitUs);
		pinMode(IrPin, OUTPUT);
	}
	
	void send(Command command){
		switch(command){
			case(Command::HiFi_ToggleStandby):
				hifi_irRemote->send(MELECTRONIC__MC_MI_1212::Command::ToggleStandby);
				break;
			case(Command::TV_ToggleStandby):
				tv_irRemote->send(FINLUX__32FLE845_Eco::Command::ToggleStandby);
				break;
			default:
				//do nothing
				break;
		}
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
