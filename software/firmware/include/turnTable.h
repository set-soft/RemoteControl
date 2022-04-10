#pragma once

namespace turnTable{
	enum class Command{
		TurnClockWise,
		TurnCounterClockWise,
	};

	void init();
	void tick();
	void sendCommand(Command command);
}