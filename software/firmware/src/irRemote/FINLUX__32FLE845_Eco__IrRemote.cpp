#include "FINLUX__32FLE845_Eco__IrRemote.h"

namespace FINLUX__32FLE845_Eco{
	static void init_Implementation(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		Philips_RC5_IrRemote::init(infraRed_on, infraRed_off, waitUs); 
	}
	void (*init)(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs) = init_Implementation;
	
	static void send_Implementation(Command command){
		switch(command){
			case FINLUX__32FLE845_Eco::Command::ToggleStandby:
				Philips_RC5_IrRemote::send(Philips_RC5_IrRemote::Address::TV1, Philips_RC5_IrRemote::Command::Standby);
				break;
			default:
				break;
		}
	}
	void (*send)(Command command) = send_Implementation;
}
