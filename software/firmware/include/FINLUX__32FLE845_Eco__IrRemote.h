#pragma once

#include "Philips_RC5_IrRemoteProtocol.h"
#include <stdint.h>

namespace FINLUX__32FLE845_Eco{
	enum class Command{
		ToggleStandby,
	};

	typedef void (*InfraRed_on)();
	typedef void (*InfraRed_off)();
	typedef void (*WaitMicroseconds)(unsigned int microSeconds);

	class IrRemote{
		public:
			IrRemote(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs);
			void send(Command command);
		private:
			Philips_RC5_IrRemote::Protocol* remoteProtocol;
	};
}
