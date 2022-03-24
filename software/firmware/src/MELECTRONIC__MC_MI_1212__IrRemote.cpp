#include "MELECTRONIC__MC_MI_1212__IrRemote.h"

namespace MELECTRONIC__MC_MI_1212{
	IrRemote::IrRemote(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		this->remoteProtocol = new Samsung_IrRemote::Protocol(infraRed_on, infraRed_off, waitUs); 
	}
	
	void IrRemote::send(Command command){
		switch(command){
			case MELECTRONIC__MC_MI_1212::Command::ToggleOnOff:
				this->remoteProtocol->send(0x0808, 0x78);
				break;
			default:
				break;
		}
		
	}
}
