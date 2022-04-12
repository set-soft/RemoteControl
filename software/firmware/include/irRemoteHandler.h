#pragma once

#include "MELECTRONIC__MC_MI_1212__IrRemote.h"

namespace irRemoteHandler{
	enum class Command{
		HiFi_ToggleStandby,
		TV_ToggleStandby,
	};

	extern void (*init)();
	extern void (*send)(Command command);
}
