#include <Arduino.h>
#include "buttons.h"

namespace buttons{
	static const pin_size_t ButtonBackLeftPin = 6;
	static const pin_size_t ButtonBackRightPin = 5;
	static const pin_size_t ButtonFrontLeftPin = 4;
	static const pin_size_t ButtonFrontRightPin = 3;
	static Buttons pressedButton = Buttons::None;

	static void backLeftPressed_interrupt();
	static void backRightPressed_interrupt();
	static void frontLeftPressed_interrupt();
	static void frontRightPressed_interrupt();

	void init(){
		pinMode(ButtonBackLeftPin, INPUT_PULLUP);
		pinMode(ButtonBackRightPin, INPUT_PULLUP);
		pinMode(ButtonFrontLeftPin, INPUT_PULLUP);
		pinMode(ButtonFrontRightPin, INPUT_PULLUP);

		attachInterrupt(digitalPinToInterrupt(ButtonBackLeftPin), backLeftPressed_interrupt, FALLING);
		attachInterrupt(digitalPinToInterrupt(ButtonBackRightPin), backRightPressed_interrupt, FALLING);
		attachInterrupt(digitalPinToInterrupt(ButtonFrontLeftPin), frontLeftPressed_interrupt, FALLING);
		attachInterrupt(digitalPinToInterrupt(ButtonFrontRightPin), frontRightPressed_interrupt, FALLING);
	}

	Buttons getPressedEvent(){
		Buttons temp = pressedButton;
		pressedButton = Buttons::None;
		return temp;
	}

	bool backLeftPressed(){
		return digitalRead(ButtonBackLeftPin) == LOW;
	}

	bool backRightPressed(){
		return digitalRead(ButtonBackRightPin) == LOW;
	}


	static void backLeftPressed_interrupt(){
		pressedButton = Buttons::BackLeft;
	}

	static void backRightPressed_interrupt(){
		pressedButton = Buttons::BackRight;
	}

	static void frontLeftPressed_interrupt(){
		pressedButton = Buttons::FrontLeft;
	}

	static void frontRightPressed_interrupt(){
		pressedButton = Buttons::FrontRight;
	}
}
