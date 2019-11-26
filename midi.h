/*
===============================================================================
 Name        : midi.h
 Author      : Daniel Glover
 Version     : Alpha
 Copyright   : $(copyright)
 Description : ** Needs description still **
===============================================================================
*/

#include <stdio.h>
#include "registerDef.h"


struct _MIDIData {
	int key;
	int velocity;
	int flag;
};

typedef struct _MIDIData MIDIData; //defining struct type

MIDIData receivedData[8];

/*
 * Configure UART for MIDI
 */
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

/*
 * Read information from MIDI
 */
void readMIDIByte(int byte) {
	if (byte == 0x3c) {
		configT2MR3(261);		// play middle c (C4)
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x3e) {
		configT2MR3(293);		// play D4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x40) {
		configT2MR3(329);		// play E4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x41) {
		configT2MR3(349);		// play F4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x43) {
		configT2MR3(391);		// play G4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x45) {
		configT2MR3(440);		// play A4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x47) {
		configT2MR3(494);		// play B4
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x48) {
		configT2MR3(523);		// play C5 (full octave)
		U0FCR |= (1 << 1); // clear FIFO Rx
	}
}

/*
 * Display what should be played on the speaker
 */
void playMIDIByte(int byte) {
	if (((U0LSR >> 0) & 1) == 1) {
		if (byte == 0x90);
		printf("data in %x\n", byte);
		readMIDIByte(byte);
//		U0FCR |= (1 << 1); // clear FIFO Rx
		receivedData[0].key = byte;
		receivedData[0].flag = 1;
		}

//	if (byte == 0x7f) {
//			receivedData[0].velocity = byte;
//			//printf("Middle C %x\n", byte);
//		}
}
