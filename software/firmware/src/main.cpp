#include <Arduino.h>
#include <ArduinoBLE.h>

void controlLed(BLEDevice peripheral);

const char* UUID = "19b10000-e8f2-537e-4f6c-d104768a1214";

const pin_size_t ButtonLeftPin = 6;
const pin_size_t ButtonRightPin = 5;

static void initLed(void);
static void setLedOn(void);
static void setLedOff(void);

static void initButtons(void);
static boolean buttonLeftPressed(void);
static boolean buttonRightPressed(void);

void setup(void){
	initLed();
	initButtons();
	BLE.begin();
}

void loop(void){
	BLEDevice peripheral = BLE.available();

	if(peripheral) {
		if(peripheral.localName() != "LED") {
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
			if(buttonLeftPressed()){
				setLedOn();
				ledCharacteristic.writeValue((byte)0x01);
			}
			else if(buttonRightPressed()){
				setLedOff();
				ledCharacteristic.writeValue((byte)0x00);
			}
		}
	}
	else{
		BLE.scanForUuid(UUID);
	}
}

static void initLed(void){
	pinMode(LED_BUILTIN, OUTPUT);
}

static void setLedOn(void){
	digitalWrite(LED_BUILTIN, HIGH);	
}

static void setLedOff(void){
	digitalWrite(LED_BUILTIN, LOW);
}

static void initButtons(void){
	pinMode(ButtonLeftPin, INPUT_PULLUP);
	pinMode(ButtonRightPin, INPUT_PULLUP);
}

static boolean buttonLeftPressed(void){
	return digitalRead(ButtonLeftPin) == LOW;
}

static boolean buttonRightPressed(void){
	return digitalRead(ButtonRightPin) == LOW;
}
