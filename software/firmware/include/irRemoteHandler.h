#pragma once

#include "MELECTRONIC__MC_MI_1212__IrRemote.h"

namespace irRemoteHandler{
	enum class Command{
		HiFi_ToggleStandby,
		TV_ToggleStandby,
	};

	void init();
	void send(Command command);
}
