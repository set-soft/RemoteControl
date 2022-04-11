#include "IrRemoteRaw.h"

namespace IrRemoteRaw{
    void sendCarrierNTimes_Implementation(uint16_t periods, Configuration configuration){
		for(uint16_t n=0; n < periods; n++){
			configuration.infraRed_on();
			configuration.waitCarrierHalfPeriod();
			configuration.infraRed_off();
			configuration.waitCarrierHalfPeriod();
		}
	}
	void (*sendCarrierNTimes)(uint16_t periods, Configuration configuration) = sendCarrierNTimes_Implementation;
}
