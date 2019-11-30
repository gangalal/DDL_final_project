#include "final.h"

MIDIData receivedData[8];

void configMIDI() {
	PCONP |= (1 << 3); //on reset UART is enable
	PCLKSEL0 &= ~(1 << 6);
	PCLKSEL0 &= ~(1 << 7);	// set UART to 1 MHz
	U0LCR |= (1 << 7); //DLAB = 1 enable DLAB
	U0DLL = 2;	// set baud rate
	U0DLM = 0;
	U0FCR |= (1 << 0);	// enable FIFO
	PINSEL0 |= (1 << 6);
	PINSEL0 &= ~(1 << 7);
	//skipped interrupts
	U0FCR |= (1 << 2);	// clear TX FIFO
	U0FCR |= (1 << 1);	// clear RX FIFO
	U0LCR |= (1 << 0);
	U0LCR |= (1 << 1);	// select word length: 8-bit
	U0LCR &= ~(1 << 2); // 1 stop bit
	// U0FCR &= ~(1 << 6);
	// U0FCR |= (1 << 7);	// These two bits determine 8 bits characters to receive
	U0LCR &= ~(1 << 7); // needs to clear
}

void playMIDIByte(int byte) {
	if (byte == 0x3c) {
		configT2MR3(259);		// play middle c (C4)
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x3e) {
		configT2MR3(291);		// play D4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x40) {
		configT2MR3(327);		// play E4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x41) {
		configT2MR3(347);		// play F4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x43) {
		configT2MR3(389);		// play G4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x45) {
		configT2MR3(437);		// play A4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x47) {
		configT2MR3(490);		// play B4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x48) {
		configT2MR3(519);		// play C5 (full octave)
		U0FCR |= (1 << 1); // clear FIFO Rx
	}

}

void readMIDIByte(int byte1, int byte2) {
	if (((U0LSR >> 0) & 1) == 1) {
		if (byte1 == 0x90);
//		printf("data in %x\n", byte);
		playMIDIByte(byte2);
//		U0FCR |= (1 << 1); // clear FIFO Rx
//		receivedData[0].key = byte;
	//	receivedData[0].flag = 1;

	}
}

void check(int* byte) {

	//printf("byte is %x\n", byte);
	/*int* data;
	 data[0]
	 */
	if ((byte[0] == 0x90) && (byte[1] == 0x3c) && (byte[2] > 0)) {

		configT2MR3(259);		// play middle c (C4)
		printf("you pressed for long time\n");
	}
	/*if ((byte[0] == 0x90) && (byte[1] == 0x3c) && (byte[2] > 0)
			&& (byte[3]> 0)) {
		printf("you pressed for little time\n");
		configT2MR3(259);		// play middle c (C4)
	}*/ else {
		configT2MR3(0);
	}
}
