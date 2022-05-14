#include <Arduino.h>
#include "buttons.h"

namespace buttons{
	static const pin_size_t ButtonBackLeftPin = 6;
	static const pin_size_t ButtonBackRightPin = 5;
	static const pin_size_t ButtonFrontLeftPin = 4;
	static const pin_size_t ButtonFrontRightPin = 3;
	static bool backLeftPressedInterrupt = false;
	static bool backRightPressedInterrupt = false;
	static bool frontLeftPressedInterrupt = false;
	static bool frontRightPressedInterrupt = false;
	static Buttons pressedButton = Buttons::None;
	static unsigned long lastPressedMillis = 0;

	static void backLeftPressed_interrupt();
	static void backRightPressed_interrupt();
	static void frontLeftPressed_interrupt();
	static void frontRightPressed_interrupt();
	static void updateLastPressedTime();

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

	static void tick_Implementation(){
		if(backLeftPressedInterrupt){
			backLeftPressedInterrupt = false;
			pressedButton = Buttons::BackLeft;
			updateLastPressedTime();
		}
		else if(backRightPressedInterrupt){
			backRightPressedInterrupt = false;
			pressedButton = Buttons::BackRight;
			updateLastPressedTime();
		}
		else if(frontLeftPressedInterrupt){
			frontLeftPressedInterrupt = false;
			pressedButton = Buttons::FrontLeft;
			updateLastPressedTime();
		}
		else if(frontRightPressedInterrupt){
			frontRightPressedInterrupt = false;
			pressedButton = Buttons::FrontRight;
			updateLastPressedTime();
		}
	}
	void (*tick)() = tick_Implementation;

	static Buttons getPressedEvent_Implementation(){
		return pressedButton;
	}
	Buttons (*getPressedEvent)() = getPressedEvent_Implementation;

	static void clearPressedEvent_Implementation(){
		pressedButton = Buttons::None;
	}
	void (*clearPressedEvent)() = clearPressedEvent_Implementation;

	static bool backLeftPressed_Implementation(){
		PinStatus pinStatus = digitalRead(ButtonBackLeftPin);
		if(pinStatus == LOW){
			updateLastPressedTime();
			return true;
		}
		else{
			return false;
		}
	}
	bool (*backLeftPressed)() = backLeftPressed_Implementation;

	static bool backRightPressed_Implementation(){
		PinStatus pinStatus = digitalRead(ButtonBackRightPin);
		if(pinStatus == LOW){
			updateLastPressedTime();
			return true;
		}
		else{
			return false;
		}
	}
	bool (*backRightPressed)() = backRightPressed_Implementation;


	static void backLeftPressed_interrupt(){
		backLeftPressedInterrupt = true;
	}

	static void backRightPressed_interrupt(){
		backRightPressedInterrupt = true;
	}

	static void frontLeftPressed_interrupt(){
		frontLeftPressedInterrupt = true;
	}

	static void frontRightPressed_interrupt(){
		frontRightPressedInterrupt = true;
	}

	static void updateLastPressedTime(){
		lastPressedMillis = millis();
	}

	static unsigned long getLastPressedMillis_Implementation(){
		return lastPressedMillis;
	}
	unsigned long (*getLastPressedMillis)() = getLastPressedMillis_Implementation;
}
