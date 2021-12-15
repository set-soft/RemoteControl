#include <Arduino.h>
#include <ArduinoBLE.h>

void controlLed(BLEDevice peripheral);

const char* UUID = "19b10000-e8f2-537e-4f6c-d104768a1214";
	
void setup(void){
	Serial.begin(9600);
	while(!Serial);
	
	BLE.begin();
	BLE.scanForUuid(UUID);
}

void loop(void) {
	BLEDevice peripheral = BLE.available();

	if(peripheral) {
		Serial.println(peripheral.localName());
		if(peripheral.localName() != "LED") {
			return;
		}
		BLE.stopScan();
		controlLed(peripheral);

		// peripheral disconnected, start scanning again => so hässlich!!!
		BLE.scanForUuid(UUID);
	}
}

void controlLed(BLEDevice peripheral) {

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
		ledCharacteristic.writeValue((byte)0x01);
		delay(500);
		ledCharacteristic.writeValue((byte)0x00);
		delay(1000);
	}
}
