#pragma once

#include <stdint.h>

namespace Philips_RC5_IrRemote{
	enum class Address{
		TV1 = 0x00,
		TV2 = 0x01,
		Teletext = 0x02,
		Video = 0x03,
		LV1 = 0x04,
		VCR1 = 0x05,
		VCR2 = 0x06,
		Experimental = 0x07,
		Sat1 = 0x08,
		Camera = 0x09,
		Sat2 = 0x0A,
		// 0x0B
		CDV = 0x0C,
		Camcorder = 0x0D,
		// 0x0E
		// 0x0F
		Pre_amp = 0x10,
		Tuner = 0x11,
		Recorder1 = 0x12,
		Pre_amp2 = 0x13,
		CD_player = 0x14,
		Phone = 0x15,
		SatA = 0x16,
		Recorder2 = 0x17,
		// 0x18
		// 0x19
		CDR = 0x1A,
		// 0x1B
		// 0x1C
		Lighting1 = 0x1D,
		Lighting2 = 0x1E,
		// 0x1F
	};

	enum class Command{
		Key0 = 0x00,
		Key1 = 0x01,
		Key2 = 0x02,
		Key3 = 0x03,
		Key4 = 0x04,
		Key5 = 0x05,
		Key6 = 0x06,
		Key7 = 0x07,
		Key8 = 0x08,
		Key9 = 0x09,
		SelectChannel = 0x0A,
		Standby = 0x0B,
		Mute = 0x0C,
		VolumeUp = 0x0D,
		VolumeDown = 0x0E,
		BrightnessUp = 0x0F,
		BrightnessDown = 0x10,
		ProgramUp = 0x11,
		ProgramDown = 0x12,
		// 0x13 - 0x31
		FastRewind = 0x32,
		// 0x33
		FastForward = 0x34,
		Play = 0x35,
		Stop = 0x36,
		Recording = 0x37,
		// 0x38 - 0x3F
	};

	typedef void (*InfraRed_on)();
	typedef void (*InfraRed_off)();
	typedef void (*WaitMicroseconds)(unsigned int microseconds);

	class Protocol{
		public:
			Protocol(const InfraRed_on infraRed_on, const InfraRed_off infraRed_off, const WaitMicroseconds waitUs);
			void send(Address address, Command command);
		private:
			const unsigned int CarrierPeriodHalf_us = 13;
			bool toggleBit = false;

			InfraRed_on infraRed_on;
			InfraRed_off infraRed_off;
			WaitMicroseconds waitUs;

			void sendStartBits();
			void sendToggleBit();
			void sendAddress(Address address);
			void sendCommand(Command command);
			void sendLowestBits(uint8_t data, uint8_t nrOfBits);
			void sendHighBit();
			void sendLowBit();
			void sendCarrierNTimes(uint16_t periods);
	};
}
