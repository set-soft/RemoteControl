#include "MELECTRONIC__MC_MI_1212__IrRemote.h"

namespace MELECTRONIC__MC_MI_1212{
	static void init_Implementation(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs){
		Samsung_IrRemote::init(infraRed_on, infraRed_off, waitUs);
	}
	void (*init)(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs) = init_Implementation;
	
	static void send_Implementation(Command command){
		switch(command){
			case MELECTRONIC__MC_MI_1212::Command::ToggleStandby:
				Samsung_IrRemote::send(0x0808, 0x78);
				break;
			default:
				break;
		}
	}
	void (*send)(Command command) = send_Implementation;
}
