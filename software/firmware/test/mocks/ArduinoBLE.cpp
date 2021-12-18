#include "ArduinoBLE.h"

int BLELocalDevice::begin(){return 0;}
int BLELocalDevice::scanForUuid(String uuid, bool withDuplicates){return 0;}
void BLELocalDevice::stopScan(){}
BLEDevice BLELocalDevice::available(){return BLEDevice();}


bool BLEDevice::connected() const{return false;}
bool BLEDevice::disconnect(){return false;}
String BLEDevice::localName() const {return "";}
bool BLEDevice::connect(){return false;}
bool BLEDevice::discoverAttributes(){return false;}
BLEDevice::operator bool() const{return false;}
BLECharacteristic BLEDevice::characteristic(const char * uuid) const{return BLECharacteristic();}


BLELocalDevice BLEObj;
BLELocalDevice& BLE = BLEObj;
