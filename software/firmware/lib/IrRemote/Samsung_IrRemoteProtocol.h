#pragma once
#include <stdint.h>

namespace Samsung_IrRemote{
	typedef void (*InfraRed_on)();
	typedef void (*InfraRed_off)();
	typedef void (*WaitMicroseconds)(unsigned int microseconds);

	void init(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs);
	void send(const uint16_t Address, const uint8_t Data);
}