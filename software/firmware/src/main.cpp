#include <Arduino.h>
#include <ArduinoBLE.h>

#include "led.h"
#include "buttons.h"
#include "irRemoteHandler.h"

const char* UUID = "19b10000-e8f2-537e-4f6c-d104768a1214";


void setup(void){
	irRemoteHandler::init();
	initLed();

	initButtons();

	initLed();
	BLE.begin();
}

void loop(void){
	if(buttonFrontLeftPressed()){
		BLE.end(); //disable BLE for a while to prevent timing interferences due to interrupts
		irRemoteHandler::send(irRemoteHandler::Command::HiFi_ToggleStandby);
		delay(1000);
		BLE.begin();
	}
	else if(buttonFrontRightPressed()){
		BLE.end(); //disable BLE for a while to prevent timing interferences due to interrupts
		irRemoteHandler::send(irRemoteHandler::Command::TV_ToggleStandby);
		delay(1000);
		BLE.begin();
	}

	BLEDevice peripheral = BLE.available();

	if(peripheral) {
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

		BLECharacteristic ledCharacteristic = peripheral.characteristic("19b10001-e8f2-537e-4f6c-d104768a1214");

		if(!ledCharacteristic) {
			peripheral.disconnect();
			return;
		}
		else if(!ledCharacteristic.canWrite()) {
			peripheral.disconnect();
			return;
		}

		while(peripheral.connected()) {
			if(buttonBackLeftPressed()){
				setLedOn();
				ledCharacteristic.writeValue((byte)0x02);
			}
			else if(buttonBackRightPressed()){
				setLedOff();
				ledCharacteristic.writeValue((byte)0x01);
			}
		}
	}
	else{
		BLE.scanForUuid(UUID);
	}
}
