#include "IrRemoteRaw.h"

namespace IrRemoteRaw{
	IrRemoteRaw::IrRemoteRaw(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitCarrierHalfPeriod waitCarrierHalfPeriod){
		this->infraRed_on = infraRed_on;
		this->infraRed_off = infraRed_off;
		this->waitCarrierHalfPeriod = waitCarrierHalfPeriod;
	}

    void IrRemoteRaw::sendCarrierNTimes(uint16_t periods){
		for(uint16_t n=0; n < periods; n++){
			this->infraRed_on();
			this->waitCarrierHalfPeriod();
			this->infraRed_off();
			this->waitCarrierHalfPeriod();
		}
	}
}
