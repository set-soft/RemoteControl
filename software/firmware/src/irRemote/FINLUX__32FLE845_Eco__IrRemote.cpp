#include "FINLUX__32FLE845_Eco__IrRemote.h"

namespace FINLUX__32FLE845_Eco{
	IrRemote::IrRemote(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		this->remoteProtocol = new Philips_RC5_IrRemote::Protocol(infraRed_on, infraRed_off, waitUs); 
	}
	
	void IrRemote::send(Command command){
		switch(command){
			case FINLUX__32FLE845_Eco::Command::ToggleStandby:
				this->remoteProtocol->send(Philips_RC5_IrRemote::Address::TV1, Philips_RC5_IrRemote::Command::Standby);
				break;
			default:
				break;
		}
		
	}
}
