#pragma once

#include <stdint.h>

namespace Samsung_IrRemote{
	typedef void (*InfraRed_on)();
	typedef void (*InfraRed_off)();
	typedef void (*WaitMicroseconds)(unsigned int microseconds);

	class Protocol{
		public:
			Protocol(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs);
			void send(const uint16_t Address, const uint8_t Data);
		private:
			const unsigned int CarrierPeriodHalf_us = 13;
			const unsigned int StartBitHalf_us = 4500;

			InfraRed_on infraRed_on;
			InfraRed_off infraRed_off;
			WaitMicroseconds waitUs;

			void sendStartBit();
			void sendCarrierNTimes(uint16_t periods);
			void sendByte(uint8_t data);
			void sendHighBit();
			void sendLowBit();
			void sendStopBit();
	};
}