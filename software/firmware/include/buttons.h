#pragma once

namespace buttons{
	enum class Buttons{
		BackLeft,
		BackRight,
		FrontLeft,
		FrontRight,
		None,
	};

	extern void (*init)();
	extern Buttons (*getPressedEvent)();
	extern bool (*backLeftPressed)();
	extern bool (*backRightPressed)();
}
