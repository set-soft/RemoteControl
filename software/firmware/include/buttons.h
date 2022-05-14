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
	extern void (*tick)();
	extern Buttons (*getPressedEvent)();
	extern void (*clearPressedEvent)();
	extern bool (*backLeftPressed)();
	extern bool (*backRightPressed)();
	extern unsigned long (*getLastPressedMillis)();
}
