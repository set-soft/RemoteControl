#pragma once

#include <stdint.h>

namespace IrRemoteRaw{
	typedef void (*InfraRed_on)();
	typedef void (*InfraRed_off)();
	typedef void (*WaitCarrierHalfPeriod)();

	class IrRemoteRaw{
		public:
			IrRemoteRaw(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitCarrierHalfPeriod waitCarrierHalfPeriod);
			void sendCarrierNTimes(uint16_t periods);
        private:
            InfraRed_on infraRed_on;
			InfraRed_off infraRed_off;
			WaitCarrierHalfPeriod waitCarrierHalfPeriod;
	};
}
