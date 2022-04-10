#include "turnTable.h"
#include <ArduinoBLE.h>

namespace turnTable{
	static const char* UUID = "19b10000-e8f2-537e-4f6c-d104768a1214";

	static BLEDevice peripheral;
	static BLECharacteristic turnCharacteristic;

	void init(){
		BLE.begin();
	}

	void tick(){
		if(!peripheral){
			peripheral = BLE.available();
			BLE.scanForUuid(UUID);
		}
		else if(!peripheral.connected())
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
		}
	}

	void sendCommand(Command command){
		switch(command){
			case Command::TurnClockWise:
				turnCharacteristic.writeValue((byte)0x01);
				break;
			case Command::TurnCounterClockWise:
				turnCharacteristic.writeValue((byte)0x02);
				break;
			default:
				//do nothing
				break;
		}

	}
}
