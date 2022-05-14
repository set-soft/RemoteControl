#pragma once

#include <stdint.h>

typedef struct{
	uint32_t TASKS_SHUTDOWN;
	uint32_t TASKS_STOP;
	uint32_t TASKS_DISABLE;
	uint32_t TASKS_LFCLKSTOP;
	uint32_t TASKS_HFCLKSTOP;

	uint32_t TASKS_START;
	uint32_t TASKS_LFCLKSTART;
	uint32_t TASKS_HFCLKSTART;
} RegisterType;

extern RegisterType *NRF_TIMER0;
extern RegisterType *NRF_TIMER1;
extern RegisterType *NRF_TIMER2;
extern RegisterType *NRF_RTC1;
extern RegisterType *NRF_CLOCK;
extern RegisterType *NRF_RADIO;

void __WFI();
