#include "remoteControl.h"
#include "buttons.h"
#include "irRemoteHandler.h"
#include "turnTable.h"
#include <Arduino.h>

namespace remoteControl{
	static void handleButtons();

	void setup(void){
		irRemoteHandler::init();
		turnTable::init();
		buttons::init();
	}

	void tick(void){
		handleButtons();
		turnTable::tick();
	}

	static void handleButtons(){
		switch(buttons::getPressedEvent()){
			case(buttons::Buttons::BackLeft):
				while(buttons::backLeftPressed()){
					turnTable::sendCommand(turnTable::Command::TurnCounterClockWise);
				}
				break;
			case(buttons::Buttons::BackRight):
				while(buttons::backRightPressed()){
					turnTable::sendCommand(turnTable::Command::TurnClockWise);
				}
				break;
			case(buttons::Buttons::FrontLeft):
				irRemoteHandler::send(irRemoteHandler::Command::HiFi_ToggleStandby);
				delay(100);
				break;
			case(buttons::Buttons::FrontRight):
				irRemoteHandler::send(irRemoteHandler::Command::TV_ToggleStandby);
				delay(100);
				break;
			default:
				//do nothing
				break;
		}
	}
}
