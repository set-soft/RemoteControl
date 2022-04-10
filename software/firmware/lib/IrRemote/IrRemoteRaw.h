#pragma once

#include <stdint.h>

namespace IrRemoteRaw{
	struct Configuration{
		void (*infraRed_on)();
		void (*infraRed_off)();
		void (*waitCarrierHalfPeriod)();
	};

	void sendCarrierNTimes(uint16_t periods, Configuration configuration);
}
