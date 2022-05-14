#include "lowPower.h"
#include <Arduino.h>

namespace lowPower{
	static void disableSensors_Implementation(){
		pinMode(PIN_ENABLE_SENSORS_3V3, OUTPUT);
		digitalWrite(PIN_ENABLE_SENSORS_3V3, LOW);

		pinMode(PIN_ENABLE_I2C_PULLUP, OUTPUT);
		digitalWrite(PIN_ENABLE_I2C_PULLUP, LOW);
	}
	void (*disableSensors)() = disableSensors_Implementation;

	static void sleep_Implementation(){
		NRF_TIMER2->TASKS_SHUTDOWN = 1;
		NRF_TIMER1->TASKS_SHUTDOWN = 1;
		NRF_TIMER0->TASKS_SHUTDOWN = 1;
		NRF_RTC1->TASKS_STOP = 1;
		NRF_CLOCK->TASKS_LFCLKSTOP = 1;
		NRF_CLOCK->TASKS_HFCLKSTOP = 1;
		NRF_RADIO->TASKS_DISABLE = 1;
		__WFI();
		NRF_RADIO->TASKS_START = 1;
		NRF_CLOCK->TASKS_HFCLKSTART = 1;
		NRF_CLOCK->TASKS_LFCLKSTART = 1;
		NRF_RTC1->TASKS_START = 1;
		NRF_TIMER0->TASKS_START = 1;
		NRF_TIMER1->TASKS_START = 1;
		NRF_TIMER2->TASKS_START = 1;
	}
	void (*sleep)() = sleep_Implementation;
}
