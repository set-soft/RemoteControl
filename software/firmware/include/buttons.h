#pragma once

namespace buttons{
	typedef void (*Callback)();

	void init();
	void setBackLeftPressedCallback(Callback callback);
	void setBackRightPressedCallback(Callback callback);
	void setFrontLeftPressedCallback(Callback callback);
	void setFrontRightPressedCallback(Callback callback);

	bool backLeftPressed();
	bool backRightPressed();
}
