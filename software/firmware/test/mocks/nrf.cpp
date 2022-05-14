#include "nrf.h"
#include "CppUTestExt/MockSupport.h"

RegisterType *NRF_TIMER0 = new RegisterType;
RegisterType *NRF_TIMER1 = new RegisterType;
RegisterType *NRF_TIMER2 = new RegisterType;
RegisterType *NRF_RTC1 = new RegisterType;
RegisterType *NRF_CLOCK = new RegisterType;
RegisterType *NRF_RADIO = new RegisterType;

void __WFI(){
	mock().actualCall("__WFI");
}
