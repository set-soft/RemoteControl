#pragma once

namespace buttons{
	enum class Buttons{
		BackLeft,
		BackRight,
		FrontLeft,
		FrontRight,
		None,
	};

	void init();
	Buttons getPressedEvent();
	bool backLeftPressed();
	bool backRightPressed();
}
