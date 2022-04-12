#pragma once

namespace turnTable{
	enum class Command{
		TurnClockWise,
		TurnCounterClockWise,
	};

	extern void (*init)();
	extern void (*tick)();
	extern void (*sendCommand)(Command command);
}