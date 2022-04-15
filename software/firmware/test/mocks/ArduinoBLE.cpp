#include "ArduinoBLE.h"
#include "CppUTestExt/MockSupport.h"

int BLECharacteristic::writeValue(uint8_t value, bool withResponse){
	mock().actualCall("BLECharacteristic::writeValue")
		.withParameter("value", value);
	CHECK_EQUAL(true, withResponse);
	return 0;
}

BLECharacteristic::operator bool() const{
	mock().actualCall("BLECharacteristic::operator bool");
	return mock().returnBoolValueOrDefault(true);
}

bool BLECharacteristic::canWrite(){
	mock().actualCall("BLECharacteristic::canWrite");
	return mock().returnBoolValueOrDefault(true);
}


int BLELocalDevice::begin(){
	mock().actualCall("BLELocalDevice::begin");
	return 0;
}

void BLELocalDevice::end(){}

int BLELocalDevice::scanForUuid(String uuid, bool withDuplicates){
	mock().actualCall("BLELocalDevice::scanForUuid")
		.withStringParameter("uuid", uuid.c_str())
		.withBoolParameter("withDuplicates", withDuplicates);
	return 0;
}

void BLELocalDevice::stopScan(){
	mock().actualCall("BLELocalDevice::stopScan");
}

BLEDevice BLELocalDevice::available(){
	mock().actualCall("BLELocalDevice::available");
	return BLEDevice();
}


bool BLEDevice::connected() const{
	mock().actualCall("BLEDevice::connected");
	return mock().returnBoolValueOrDefault(true);
}

bool BLEDevice::disconnect(){
	mock().actualCall("BLEDevice::disconnect");
	return true;
}

String BLEDevice::localName() const {
	mock().actualCall("BLEDevice::localName");
	return String(mock().returnStringValueOrDefault("TurnTable"));
}

bool BLEDevice::connect(){
	mock().actualCall("BLEDevice::connect");
	return mock().returnBoolValueOrDefault(true);
}

bool BLEDevice::discoverAttributes(){
	mock().actualCall("BLEDevice::discoverAttributes");
	return mock().returnBoolValueOrDefault(true);
}

BLEDevice::operator bool() const{
	mock().actualCall("BLEDevice::operator bool");
	return mock().returnBoolValueOrDefault(true);
}

BLECharacteristic BLEDevice::characteristic(const char * uuid) const{
	mock().actualCall("BLEDevice::characteristic")
		.withStringParameter("uuid", uuid);
	return BLECharacteristic();
}


BLELocalDevice BLEObj;
BLELocalDevice& BLE = BLEObj;
