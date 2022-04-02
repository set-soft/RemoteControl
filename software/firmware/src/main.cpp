#include <Arduino.h>
#include <ArduinoBLE.h>

#include "led.h"
#include "buttons.h"
#include "irRemoteHandler.h"

enum class PressedButton{
	BackLeft,
	BackRight,
	FrontLeft,
	FrontRight,
	None,
};

static PressedButton pressedButton = PressedButton::None;
static const char* UUID = "19b10000-e8f2-537e-4f6c-d104768a1214";
BLEDevice peripheral;
static bool peripheralReady = false;
BLECharacteristic turnCharacteristic;

void buttonBackLeftPressed(){
	pressedButton = PressedButton::BackLeft;
}

void buttonBackRightPressed(){
	pressedButton = PressedButton::BackRight;
}

void buttonFrontLeftPressed(){
	pressedButton = PressedButton::FrontLeft;
}

void buttonFrontRightPressed(){
	pressedButton = PressedButton::FrontRight;
}

void setup(void){
	irRemoteHandler::init();
	initLed();

	initLed();
	BLE.begin();
	peripheralReady = false;
	//BLE.scanForUuid(UUID);
	//turnTable::init();

	buttons::init();
	buttons::setBackLeftPressedCallback(buttonBackLeftPressed);
	buttons::setBackRightPressedCallback(buttonBackRightPressed);
	buttons::setFrontLeftPressedCallback(buttonFrontLeftPressed);
	buttons::setFrontRightPressedCallback(buttonFrontRightPressed);
}

void loop(void){
	switch(pressedButton){
		case(PressedButton::BackLeft):
			while(peripheralReady && buttons::backLeftPressed()){
				turnCharacteristic.writeValue((byte)0x02);
			}
			pressedButton = PressedButton::None;
			break;
		case(PressedButton::BackRight):
			while(peripheralReady && buttons::backRightPressed()){
				turnCharacteristic.writeValue((byte)0x01);
			}
			pressedButton = PressedButton::None;
			break;
		case(PressedButton::FrontLeft):
			irRemoteHandler::send(irRemoteHandler::Command::HiFi_ToggleStandby);
			delay(100);
			pressedButton = PressedButton::None;
			break;
		case(PressedButton::FrontRight):
			irRemoteHandler::send(irRemoteHandler::Command::TV_ToggleStandby);
			delay(100);
			pressedButton = PressedButton::None;
			break;
		default:
			//do nothing
			break;
	}


	if(!peripheral){
		peripheral = BLE.available();
		peripheralReady = false;
		BLE.scanForUuid(UUID);
	}
	else if(!peripheral.connected()){
		peripheralReady = false;

		//BLE.scanForUuid(UUID);

		if(peripheral.localName() != "TurnTable") {
			return;
		}

		BLE.stopScan();
		
		if(!peripheral.connect()){
			return;
		}
		
		if(!peripheral.discoverAttributes()) {
			peripheral.disconnect();
			return;
		}

		turnCharacteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");

		if(!turnCharacteristic) {
			peripheral.disconnect();
			return;
		}
		else if(!turnCharacteristic.canWrite()) {
			peripheral.disconnect();
			return;
		}
		peripheralReady = true;
	}
	else{
		peripheralReady = true;
	}



	/*BLEDevice peripheral = BLE.available();

	if(peripheral && !peripheralReady) {
		if(peripheral.localName() != "TurnTable") {
			return;
		}
		BLE.stopScan();

		if(!peripheral.connect()){
			return;
		}

		if(!peripheral.discoverAttributes()) {
			peripheral.disconnect();
			return;
		}

		turnCharacteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");

		if(!turnCharacteristic) {
			peripheral.disconnect();
			return;
		}
		else if(!turnCharacteristic.canWrite()) {
			peripheral.disconnect();
			return;
		}

		while(peripheral.connected()) {
			if(buttons::backLeftPressed()){
				setLedOn();
				turnCharacteristic.writeValue((byte)0x02);
			}
			else if(buttons::backRightPressed()){
				setLedOff();
				turnCharacteristic.writeValue((byte)0x01);
			}
		}
		peripheralReady = true;
	}
	else if(!peripheral || !peripheral.connected()){
		peripheralReady = false;
		BLE.scanForUuid(UUID);
	}*/
}
