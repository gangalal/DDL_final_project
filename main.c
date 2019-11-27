/*
===============================================================================
 Name        : DanielWayofCodingFinalProject.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

#define PCONP (*(volatile unsigned int *)(0x400FC0C4))
#define PCLKSEL0 (*(volatile unsigned int *)(0x400FC1A8))   // Timer 0 Clock select
#define PCLKSEL1 (*(volatile unsigned int *)(0x400FC1AC))   // Timer 2 Clock select

#define PINSEL0 (*(volatile unsigned int *)(0x4002C000))
#define PINSEL1 (*(volatile unsigned int *)(0x4002C004))
#define PINMODE0 (*(volatile unsigned int *)(0x4002C040))
#define PINMODE1 (*(volatile unsigned int *)(0x4002C044))

#define FIO0DIR (*(volatile unsigned int *)(0x2009c000))
#define FIO0PIN (*(volatile unsigned int *)(0x2009c014))
#define FIO2DIR (*(volatile unsigned int *)(0x2009c040))      // GPIO 2
#define FIO2PIN (*(volatile unsigned int *)(0x2009c054))
#define FIO2PIN0 (*(volatile unsigned char *)(0x2009C054))

#define I2CPADCFG (*(volatile unsigned int *)(0x4002C07C))  // I2C for EEProm
#define I2C0SCLH (*(volatile unsigned int *)(0x4001C010))
#define I2C0SCLL (*(volatile unsigned int *)(0x4001C014))
#define I2C0CONSET (*(volatile unsigned int *)(0x4001C000))
#define I2C0CONCLR (*(volatile unsigned int *)(0x4001C018))
#define I2C0DAT (*(volatile unsigned int *)(0x4001C008))

#define T0TCR (*(volatile unsigned int *)(0x40004004))		// Timer 0
#define T0TC (*(volatile unsigned int *)(0x40004008))		// Timer Counter
#define T2TCR (*(volatile unsigned int *)(0x40090004))		// Timer 2 Timer Control Register
#define T2TC (*(volatile unsigned int *)(0x40090008))		// Timer 2 Timer Counter
#define T2EMR (*(volatile unsigned int *)(0x4009003C))		// EMR Match Register for Timer 2
#define T2MCR (*(volatile unsigned int *)(0x40090014))		// MCR Match Register for Timer 2
#define T2CTCR (*(volatile unsigned int *)(0x40090070))		// Count Control Register for Timer 2 Selects timer/counter mode
#define T2MR3 (*(volatile unsigned int *)(0x40090024))		// Timer 2 Match Register 3
#define T3TCR (*(volatile unsigned int *)(0x40094004))		// Timer 3 Timer Control Register
#define T3TC (*(volatile unsigned int *)(0x40094008))		// Timer 3 Timer Counter
#define T3EMR (*(volatile unsigned int *)(0x4009403C))		// EMR Match Register for Timer 3
#define T3MCR (*(volatile unsigned int *)(0x40090014))		// MCR Match Register for Timer 3
#define T3CTCR (*(volatile unsigned int *)(0x40090070))		// Count Control Register for Timer 3 - selects timer/counter Mode
#define T3MR0 (*(volatile unsigned int *)(0x40090024))		// Timer 3 Match Register 0

#define DACR (*(volatile unsigned int *)(0x4008C000))       // DAC Register

#define U0LCR (*(volatile unsigned int *)(0x4000C00C))
#define U0DLL (*(volatile unsigned int *)(0x4000C000))
#define U0DLM (*(volatile unsigned int *)(0x4000C004))
#define U0FDR (*(volatile unsigned int *)(0x4000C028))      //fractional dividing register
#define U0FCR (*(volatile unsigned int *)(0x4000C008))
#define U0ACR (*(volatile unsigned int *)(0x4000C020))
#define U0TER (*(volatile unsigned int *)(0x4000C030))
#define U0LSR (*(volatile unsigned int *)(0x4000C014))
#define U0RBR (*(volatile unsigned int *)(0x4000c000))

// Configure MIDI Keyboard for inputs
struct _MIDIData {
	int key;
	int velocity;
	int flag;
};

typedef struct _MIDIData MIDIData; //defining struct type

MIDIData receivedData[25];

/*
 * Declare and define waveform displays for LCD
 */
int square [] = {0x43, 0x68, 0x6f, 0x6f, 0x73, 0x65, 0x20, 0x77, 0x61, 0x76, 0x65, 0x66, 0x6f, 0x72, 0x6d};
int squareLen = sizeof(square);
int triangle [] = {0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E};
int triangleLen = sizeof(triangle);
// TODO Need to figure this out
int sine [] = {0x42, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E};
int sineLen = sizeof(sine);

/**
 *  Start Timer 0
 */
static inline void timer0Start() {
	T0TCR |= (1 << 0);
}

/**
 * Initialize Timer 0
 */
void timer0Init() {
	PCONP |= (1 << 1);			// Timer 0 Enable
	PCLKSEL0 &= ~(3 << 2);	// Reset clock selection on Timer 0, default = 1MHz
	timer0Start();
}

/**
 * Stop Timer 0
 */
static inline void timer0Stop() {
	T0TCR &= ~(1 << 0);
}

/**
 * Clear Timer 0 Counter
 */
static inline void timer0Reset() {
	T0TCR |= (1 << 1);
	while (T0TC != 0) {
		// wait until timer has changed
	}
	T0TCR &= ~(1 << 1);	//
}

/**
 * Read Timer 0
 */
static inline int timer0Read_us(void) {
	return T0TC; // Read Timer 0 Counter
}

/**
 *  True read Timer 0 for floating value in DACR conversion
 */
static inline float timer0Read(void) {
	return timer0Read_us() / 1000000.0;
}

/**
 * wait function in microseconds
 */
void wait_us(float usec) {
	timer0Start();
	timer0Reset();
	while (timer0Read_us() < usec) {
	}
}

void wait_ticks(unsigned long count) {
	volatile int ticks;
	for (ticks = 0; ticks < count; ticks++) {
		// do nothing
		for (int i = 0; i < 256; i++) {

		}
	}
}

/**
 * wait function in seconds
 */
void wait(float sec) {
	wait_us(sec * 1000000);
}

/**
 * Start Timer 2
 */
static inline void timer2Start() {
	T2TCR |= (1 << 0);
}

/**
 * Reset Timer 2
 */
static inline void timer2Reset() {
	T2TCR |= (1 << 1);
	while (T2TC != 0) {
		// wait until timer has changed
	}
	T2TCR &= ~(1 << 1);	//
}

/**
 * waits for count*1 second
 */
void waitOneSecond(unsigned long count) {
	volatile int ticks;
	volatile int temp = 157142 * count;
	for (ticks = 0; ticks < temp; ticks++) {
		// wait...
	}
}

/**
 * Initialize Timer 2 to control the timing of decay for each tone
 */
void timer2Init() {
	PCONP |= (1 << 22);		// Timer 2 Enable
	PCLKSEL1 &= ~(1 << 12); // Reset clock selection on Timer 2, default = 1MHz
	PCLKSEL1 &= ~(1 << 13); // Reset clock selection on Timer 2, default = 1MHz
	PINSEL0 |= (1 << 18);	// Select Timer 2, Match register 3 on LPC P0.9
	PINSEL0 |= (1 << 19); // Select Timer 2, Match register 3 on LPC P0.9
	T2MCR |= (1 << 10);	// Set Reset on MR3, TC will be reset if MR3 matches it
	T2EMR |= (3 << 10); // Toggle on match EMC3
	T2CTCR &= ~(1 << 0);
	T2CTCR &= ~(1 << 1);
	timer2Start();
}

/**
 * Configure Timer 2 for frequency generation
 */
void configT2MR3(int freq) {
	timer0Reset();			// Reset Timer 0
	T2MR3 = (1000000 / (2 * freq));	// load T2MR3 with match value based on frequency PCLK/(2*freq)
	timer2Reset();
	while (timer0Read_us() < 1000000.0) {
		int aout = (1 - (timer0Read_us() / 1000000.0)) * 1023.0;
		DACR = aout << 6;
	}
}

// play frequencies through match register (NO AOUT)
void matchFreq(int freq) {
	timer0Reset();			// Reset Timer 0
	T2MR3 = (1000000 / (2 * freq));	// load T2MR3 with match value based on frequency PCLK/(2*freq)
	timer2Reset();

}

// for calculated wait time, generate desired waveform
void genFreq(int waitTime) {
	for (int i = 0; i < 1023; i++) {
		DACR = i << 6;
		wait_us(waitTime);
		DACR = 0;
		wait_us(waitTime);
	}
}

/**
 * Start Timer 3
 */
static inline void timer3Start() {
	T3TCR |= (1 << 0);
}

/**
 * Reset Timer 3
 */
static inline void timer3Reset() {
	T3TCR |= (1 << 1);
	while (T3TC != 0) {
		// wait until timer has changed
	}
	T3TCR &= ~(1 << 1);	//
}

/*
 * Read Timer 3 in microseconds
 */
int timer3Read_us() {

	return T0TC; // Read Timer 0 Counter

}

/*
 * Wait function for Timer 3 in microseconds
 */
void wait3_us(int usec) {

	timer3Start();
	timer3Reset();
	while(timer3Read_us() < usec) {
	}
}


/**
 * Initialize Timer 3 to control the timing of decay for each tone
 */
void timer3Init() {
	PCONP |= (1 << 23);		// Timer 2 Enable
	PCLKSEL1 &= ~(1 << 14); // Reset clock selection on Timer 2, default = 1MHz
	PCLKSEL1 &= ~(1 << 15); // Reset clock selection on Timer 2, default = 1MHz
	PINSEL0 |= (1 << 20);	// Select Timer 2, Match register 3 on LPC P0.9
	PINSEL0 |= (1 << 21); // Select Timer 2, Match register 3 on LPC P0.9
	T3MCR |= (1 << 1);	// Set Reset on MR3, TC will be reset if MR3 matches it
	T3EMR |= (3 << 4); // Toggle on match EMC3
	T3CTCR &= ~(1 << 0);
	T3CTCR &= ~(1 << 1);
	timer3Start();

}

/**
 * Configure Timer 3 for frequency generation
 */
void configT3MR0(int freq) {
	timer0Reset();			// Reset Timer 0
	T3MR0 = (1000000 / (2 * freq));	// load T2MR3 with match value based on frequency PCLK/(2*freq)
	timer3Reset();
}

//** LCD Display is wired to our LPC as follows:
//** DB0-DB7 -> pins 42-49
//** E (Enable) -> pin 50 (p2.8)
//** Rs (data/instruction) -> pin 52 (p2.11)
// Configure GPIO pins for output to write to LCD display
void lcdInit() {
	FIO2DIR |= (1 << 0);
	FIO2DIR |= (1 << 1);
	FIO2DIR |= (1 << 2);
	FIO2DIR |= (1 << 3);
	FIO2DIR |= (1 << 4);
	FIO2DIR |= (1 << 5);
	FIO2DIR |= (1 << 6);
	FIO2DIR |= (1 << 7);
	FIO2DIR |= (1 << 8);
	FIO2DIR |= (1 << 11);

// set all pins low initially
	FIO2PIN &= ~(1 << 0);
	FIO2PIN &= ~(1 << 1);
	FIO2PIN &= ~(1 << 2);
	FIO2PIN &= ~(1 << 3);
	FIO2PIN &= ~(1 << 4);
	FIO2PIN &= ~(1 << 5);
	FIO2PIN &= ~(1 << 6);
	FIO2PIN &= ~(1 << 7);
	FIO2PIN &= ~(1 << 8);
	FIO2PIN &= ~(1 << 11);
}

// Configure LCD Instruction for commands
void LCDCmd(int data) {
	FIO2PIN &= ~(1 << 11); // Set Rs = 0 for cmd (clear bit 11)
	FIO2PIN0 = data; // set up DB0 - DB7
	FIO2PIN |= (1 << 8); // pulse E high
	FIO2PIN &= ~(1 << 8); // pulse E low
	wait_us(100); // wait 100 usec
}

// Initialize LCD (COMMANDS) ** optional can call from main as well
void LCDinitCmd(void) {
	LCDCmd(0x38); // Function Set
	LCDCmd(0x0E); // Turn display on, cursor on, no cursor blinking
	LCDCmd(0x06); // Entry mode cmd, cursor move L to R
	LCDCmd(0x01); // clear display
	wait_us(4000); // wait 4ms to clear display
}

// Configure LCD Instruction for Characters
 void LCDchar(int data) {
	 FIO2PIN0 = data; // set up DB0 - DB7 for ASCII codes for characters
	 FIO2PIN |= (1 << 11); // Set Rs = 1 for character (bit 11 goes high)
	 FIO2PIN |= (1 << 8); // pulse E high
	 FIO2PIN &= ~(1 << 8); // pulse E low
	 wait_us(100); // wait 100 usec
}

// Initialize LCD (CHARACTERS) ** optional can call from main as well
void LCDinitChar(void) {
	LCDCmd(0x38); // Function Set
	LCDCmd(0x0E); // Turn display on, cursor on, no cursor blinking
	LCDCmd(0x06); // Entry mode cmd, cursor move L to R
	LCDCmd(0x01); // clear display
	wait_us(4000); // wait 4ms to clear display
}

/*
 * Write a single character to LCD display
 */
void displayChar(int data) {
	FIO2PIN0 = data;
	FIO2PIN |= (1 << 11); //set Rs high
	FIO2PIN |= (1 << 8); // pulse E high
	FIO2PIN &= ~(1 << 8); // pulse E low
	wait_us(100); // wait 100 usec
}

/*
 * Write words to LCD display
 */
void displayWords(int* array, int arraySize) {
	 for(int i = 0; i<arraySize; i++) {
	 	displayChar(array[i]);
	 }
	 if (arraySize<20) {
		 for(int i = 0; i <(20-arraySize); i++) {
			 displayChar(0x20);
		 }
	 }
}

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


// I2C initialize
void I2CInit() {
	PCONP |= (1 << 7); //resetting power control for I2C0
	PCLKSEL0 &= ~(1 << 15) | (1 << 14); // resetting clock selection
	PCLKSEL0 |= (0 << 15) | (0 << 14); //dividing CCLK by 8 *needs to review
	// set high and low clk time for 1MHz clk/10 = 100kHz
	I2C0SCLH = 5;
	I2C0SCLL = 5;
	PINSEL1 |= (1 << 22) | (0 << 23); //enabling SDA0 on pin p0.27
	PINSEL1 |= (1 << 24) | (0 << 25); //enabling SCL0 on pin p0.28
	//I2CPADCFG |= (0<<2); //configuring I2C0 register to standard mode
	I2C0CONSET = (1 << 6);
}

// I2C Start Function
void I2CStart() {
	I2C0CONSET = (1 << 3); //set SI while configuring other bits
	I2C0CONSET = (1 << 5); //set STA to start condition
	I2C0CONCLR = (1 << 3); //clear SI to active state machine
	while (((I2C0CONSET >> 3) & 1) == 0) {
		//wait for start condition to be set
	}
	I2C0CONCLR = (1 << 5); //clear STA
}

// I2C write function
void I2CWrite(int data) {
	I2C0DAT = data;
	I2C0CONCLR = (1 << 3); //clear SI to standard data
	while (((I2C0CONSET >> 3) & 1) == 0) {
		//wait for write condition to be set
	}

	//check I2C0STAT for ack or nak
}

// I2C read function
int I2CRead(int ack) {
	if (ack) {
		I2C0CONSET = (1 << 2);
	} else {
		I2C0CONCLR = (1 << 2);
	}
	//I2C0CONCLR = (1 << 2);
	I2C0CONCLR = (1 << 3); //clear SI to start read
	while (((I2C0CONSET >> 3) & 1) == 0) {
		//wait for read condition to be set
	}

	return I2C0DAT;
}

// I2C Stop Function
void I2CStop() {
	I2C0CONSET = (1 << 4); //set STO to request stop condition
	I2C0CONCLR = (1 << 3); //clear SI to active state machine
	while (((I2C0CONSET >> 4) & 1) == 1) {
		//wait for stop condition to be set
	}
}

void memWrite(int* data) {
	int addr = 0b1010000; // EEprom address
	I2CStart();
	I2CWrite(addr << 1); // last bit 0 for write
	I2CWrite(32); // address to write to
	for (int i = 0; i<25; i++){ // index array values
		I2CWrite(data[i]); // write in array index value
	}
	I2CStop();
	wait_us(100);
}

void memRead(int* data) {
	int addr = 0b1010000; // EEprom address
	int count = 0;
	I2CStart();
	I2CWrite(addr << 1); // last bit 0 for write
	I2CWrite(32);
	I2CStart();
	I2CWrite((addr << 1) + 1); // last bit shifted to 1 for read
	for (int i = 0; i<25;i++) {
		if (i<24) {
			int tester = I2CRead(1);
			if (tester == data[i]){
				count++;
		  } else {
			int tester = I2CRead(0);
				if (tester == data[i]) {
				count++;
				}
			}
		}
	}
	I2CStop();
	wait_us(100);
	if (count == 25) { // if the counter sees the correct 25 notes
		// insert printf command or LCD screen shot

}

void playMIDIByte(int byte) {
	if (byte == 0x3c) {
		matchFreq(259);		// play middle c (C4)
		memWrite(byte);
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x3e) {
		matchFreq(291);		// play D4
		memWrite(byte);
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x40) {
		matchFreq(327);		// play E4
		memWrite(byte);
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x41) {
		matchFreq(347);		// play F4
		memWrite(byte);
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x43) {
		matchFreq(389);		// play G4
		memWrite(byte);
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x45) {
		matchFreq(437);		// play A4
		memWrite(byte);
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x47) {
		matchFreq(490);		// play B4
		memWrite(byte);
		U0FCR |= (1 << 1); // clear FIFO Rx
	} else if (byte == 0x48) {
		matchFreq(519);		// play C5 (full octave)
		memWrite(byte);
		U0FCR |= (1 << 1); // clear FIFO Rx
	}

}

void readMIDIByte(int byte) {
	if (((U0LSR >> 0) & 1) == 1) {
		if (byte == 0x90);
//		printf("data in %x\n", byte);
		playMIDIByte(byte);
//		U0FCR |= (1 << 1); // clear FIFO Rx
//		receivedData[0].key = byte;
//		receivedData[0].flag = 1;

	}
}

//	if (byte == 0x7f) {
//			receivedData[0].velocity = byte;
//			//printf("Middle C %x\n", byte);
//		}
}

/*
 * Generate a square waveform
 */
void squareWave(void) {

}

/*
 * Generate a triangle waveform
 */
void triangleWave(void) {

}

/*
 * Generate a sine waveform
 */
void sineWave(void) {

}

/*
 * Generate a slow click track
 */
void slowClick(void) {

}

/*
 * Generate a normal click track
 */
void normalClick(void) {

}

/*
 * Generate a fast click track
 */
void fastClick(void) {

}

/*
 * Initialize pins as inputs and outputs
 * Initialize pull-up/pull-down resistors
 * for the 4x4 keypad
 */
void keypadInit(void) {

	/*
	 * Set pins 8-11 as outputs - "rows"
	 * Set pins 12-15 as inputs - "columns"
	 */
	FIO0DIR |= (1 << 6);	// Pin 8 	- 	Row 1
	FIO0DIR |= (1 << 0);	// Pin 9 	- 	Row 2
	FIO0DIR |= (1 << 1);	// Pin 10 	- 	Row 3
	FIO0DIR |= (1 << 18);	// Pin 11 	- 	Row 4
	FIO0DIR &= ~(1 << 17);	// Pin 12 	- 	Column 1
	FIO0DIR &= ~(1 << 15);	// Pin 13	-	Column 2
	FIO0DIR &= ~(1 << 16);	// Pin 14	-	Column 3
	FIO0DIR &= ~(1 << 23);	// Pin 15	-	Column 4

	/*
	 * Set pins 8-11 low
	 */
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);

	/*
	 * Set pins 12-15 with internal pull down resistors
	 * See the above question
	 */
	PINMODE1 |= (1 << 2) | (1 << 3);
	PINMODE0 |= (1 << 30) | (1 << 31);
	PINMODE1 |= (1 << 0) | (1 << 1);
	PINMODE1 |= (1 << 14) | (1 << 15);

}

/*
 * Set pins 8-11 low
 */
void rowReset() {

	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);
	wait_us(250);

}

/*
 * Set Row 1 high, the rest low
 */
void setRow1(void) {

	FIO0PIN |= (1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);
	wait_us(250);

}

/*
 * Set Row 2 high, the rest low
 */
void setRow2(void) {

	FIO0PIN |= (1 << 0);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);
	wait_us(250);

}

/*
 * Set Row 3 high, the rest low
 */
void setRow3(void) {

	FIO0PIN |= (1 << 1);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 18);
	wait_us(250);

}

/*
 * Set Row 4 high, the rest low
 */
void setRow4(void) {

	FIO0PIN |= (1 << 18);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	wait_us(250);

}

/*
 * Determine if a key in Row 1 has been pressed and prints test statement
 */
void checkRow1(void) {

	setRow1();
	wait_us(250);

	/*
	 * Row 1 of the keypad corresponds to waveform selection
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf("You have selected the square waveform.\n");
		wait_us(50000);
		// TODO input command for square waveform & LCD display info
		squareWave();
		displayWords(square,squareLen);
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf("You have selected the triangle waveform.\n");
		wait_us(50000);
		// TODO input command for triangle waveform & LCD display info
		triangleWave();
		displayWords(triangle,triangleLen);
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf("You have selected the sine waveform.\n");
		wait_us(50000);
		// TODO input command for sine waveform & LCD display info
		sineWave();
		displayWords(sine,sineLen);
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf("You have pressed A.\n");
		wait_us(50000);
	}

	wait_us(50000);
	rowReset();
	wait_us(250);

}

/*
 * Row 2 of the keypad corresponds to click track speed
 */
void checkRow2(void) {

	setRow2();
	wait_us(250);

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf("You have selected the slow click track speed.\n");
		wait_us(50000);
		// TODO input command for slow click track speed & LCD display info
		slowClick();
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf("You have selected the normal click track speed.\n");
		wait_us(50000);
		// TODO input command for normal click track speed & LCD display info
		normalClick();
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf("You have selected the high click track speed.\n");
		wait_us(50000);
		// TODO input command for high click track speed & LCD display info
		fastClick();
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf("You have pressed B.\n");
		wait_us(50000);
	}
	wait_us(50000);
	rowReset();
	wait_us(250);

}

/*
 * Determine if a key in Row 3 has been pressed and prints test statement
 */
void checkRow3(void) {

	setRow3();
	wait_us(250);

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf("You have pressed 7.\n");
		wait_us(50000);
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf("You have pressed 8.\n");
		wait_us(50000);
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf("You have pressed 9.\n");
		wait_us(50000);
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf("You have pressed C.\n");
		wait_us(50000);
	}

	wait_us(50000);
	rowReset();
	wait_us(250);
}

/*
 * Determine if a key in Row 4 has been pressed and prints test statement
 */
void checkRow4(void) {

	setRow4();
	wait_us(250);

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf("You have pressed *.\n");
		wait_us(50000);
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf("You have pressed 0.\n");
		wait_us(50000);
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf("You have pressed #.\n");
		wait_us(50000);
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf("You have pressed D.\n");
		wait_us(50000);
	}

	wait_us(50000);
	rowReset();
	wait_us(250);

}

/*
 * Scan for pressed key
 * We can combine the checkRow functions if we want to - kept it separate until
 * we determine which rows we will be using. This will depend on how many
 * functions we end up needing to use on the keypad.
 */
void keyScan() {

	checkRow1();
	checkRow2();
	checkRow3();
	checkRow4();

}

int main(void) {
	PINSEL1 |= (1 << 21); 	// enable AOUT pin 18
	PINSEL1 &= ~(1 << 20);	// enable AOUT pin 18
	// initialize timers
	timer0Init();
	timer2Init();

	/*lcdInit();
	 timer0Init();
	 //LCDinitCmd();
	 LCDinitChar();
	 displayChar(0x46);
	 displayChar(0x21);*/

	configMIDI(); // configure MIDI keyboard
	wait_us(100);

	keypadInit();	// configure 4x4 keypad
	wait_us(100);

	unsigned char bytearray[25]; // create an empty char array to hold 25 bytes (one for each note played)

	while (1) {

	}
	return 0;
}
