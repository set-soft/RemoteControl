#pragma once

#include "Samsung_IrRemoteProtocol.h"
#include <stdint.h>

namespace MELECTRONIC__MC_MI_1212{
	enum class Command{
		ToggleStandby,
	};

	typedef void (*InfraRed_on)();
	typedef void (*InfraRed_off)();
	typedef void (*WaitMicroseconds)(unsigned int microSeconds);

	void init(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs);
	void send(Command command);
}
