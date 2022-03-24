#pragma once

#include "String.h"

class BLECharacteristic{
public:
	int writeValue(uint8_t value, bool withResponse = true);
	operator bool() const;
	bool canWrite();
};

class BLEDevice{
public:
	virtual bool connected() const;
	virtual bool disconnect();
	String localName() const;
	bool connect();
	bool discoverAttributes();
	virtual operator bool() const;
	BLECharacteristic characteristic(const char * uuid) const;
};

class BLELocalDevice{
public:
	virtual int begin();
	virtual void end();
	virtual int scanForUuid(String uuid, bool withDuplicates = false);
	virtual void stopScan();
	virtual BLEDevice available();
};






extern BLELocalDevice& BLE;
