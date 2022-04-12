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

	static void init_Implementation(){
		pinMode(ButtonBackLeftPin, INPUT_PULLUP);
		pinMode(ButtonBackRightPin, INPUT_PULLUP);
		pinMode(ButtonFrontLeftPin, INPUT_PULLUP);
		pinMode(ButtonFrontRightPin, INPUT_PULLUP);

		attachInterrupt(digitalPinToInterrupt(ButtonBackLeftPin), backLeftPressed_interrupt, FALLING);
		attachInterrupt(digitalPinToInterrupt(ButtonBackRightPin), backRightPressed_interrupt, FALLING);
		attachInterrupt(digitalPinToInterrupt(ButtonFrontLeftPin), frontLeftPressed_interrupt, FALLING);
		attachInterrupt(digitalPinToInterrupt(ButtonFrontRightPin), frontRightPressed_interrupt, FALLING);
	}
	void (*init)() = init_Implementation;

	static Buttons getPressedEvent_Implementation(){
		Buttons temp = pressedButton;
		pressedButton = Buttons::None;
		return temp;
	}
	Buttons (*getPressedEvent)() = getPressedEvent_Implementation;

	static bool backLeftPressed_Implementation(){
		return digitalRead(ButtonBackLeftPin) == LOW;
	}
	bool (*backLeftPressed)() = backLeftPressed_Implementation;

	static bool backRightPressed_Implementation(){
		return digitalRead(ButtonBackRightPin) == LOW;
	}
	bool (*backRightPressed)() = backRightPressed_Implementation;


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
