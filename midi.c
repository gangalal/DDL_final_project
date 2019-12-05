#include "final.h"

int receivedData[25];
int noteLength[25];

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

void recordSquareWF(int* byte) {
	timer1Reset();
	timer1Start();
	if (byte[0] == 0x3c) {
		configT2MR3(259);// play middle c (C4)
		receivedData[count] = 0x3c;
		count++;
	} else if (byte[0] == 0x3e) {
		configT2MR3(291);// play D4
		receivedData[count] = 0x3e;
		count++;
	} else if (byte[0] == 0x40) {
		configT2MR3(327);		// play E4
		receivedData[count] = 0x40;
		count++;
	} else if (byte[0] == 0x41) {
		configT2MR3(347);		// play F4
		receivedData[count] = 0x41;
		count++;
	} else if (byte[0] == 0x43) {
		configT2MR3(389);		// play G4
		receivedData[count] = 0x43;
		count++;
	} else if (byte[0] == 0x45) {
		configT2MR3(437);		// play A4
		receivedData[count] = 0x45;
		count++;
	} else if (byte[0] == 0x47) {
		configT2MR3(490);		// play B4
		configT3MR0(0);
		receivedData[count] = 0x47;
		count++;
	} else if (byte[0] == 0x48) {
		configT2MR3(519);		// play C5 (full octave)
		receivedData[count] = 0x48;
		count++;
	}
	timer1Stop();
	noteLength[count] = timer1Read_us();

}

void recordTriangleWF(int* byte) {
	timer1Reset();
	timer1Start();
	if (byte[0] == 0x3c) {
		triangleWave(700, 35);		// play middle c (C4)
		receivedData[count] = 0x3c;
		count++;
		printf("count %d\n", count);
	} else if (byte[0] == 0x3e) {
		triangleWave(700, 40);		// play D4
		receivedData[count] = 0x3e;
		count++;
		printf("count %d\n", count);
	} else if (byte[0] == 0x40) {
		triangleWave(700, 45);		// play E4
		receivedData[count] = 0x40;
		count++;
		printf("count %d\n", count);
	} else if (byte[0] == 0x41) {
		triangleWave(700, 47);		// play F4
		receivedData[count] = 0x41;
		count++;
		printf("count %d\n", count);
	} else if (byte[0] == 0x43) {
		triangleWave(700, 55);		// play G4
		receivedData[count] = 0x43;
		count++;
		printf("count %d\n", count);
	} else if (byte[0] == 0x45) {
		triangleWave(700, 60);		// play A4
		receivedData[count] = 0x45;
		count++;
		printf("count %d\n", count);
//		} else if (byte[0] == 0x47) {
//			configT2MR3(490);		// play B4
//			receivedData[count] = 0x47;
//			count++;
//			printf("count %d\n", count);
	} else if (byte[0] == 0x48) {
		triangleWave(700, 75);		// play C5 (full octave)
		receivedData[count] = 0x48;
		count++;
		printf("count %d\n", count);
	}
	timer1Stop();
	noteLength[count] = timer1Read_us();

}


void playMIDIChord(int* byte) {
	if (byte[0] == 0x3c) {
		configT2MR3(327);

		//configT2Chord(259, 327);
		// play middle c (C4)
	}

}

