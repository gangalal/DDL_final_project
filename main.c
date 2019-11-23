/*
 ===============================================================================
 Name        : DDL_Final_Project.c
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
#define PCLKSEL0 (*(volatile unsigned int *)(0x400FC1A8)) 	// Timer 0 Clock select
#define PCLKSEL1 (*(volatile unsigned int *)(0x400FC1AC)) 	// Timer 2 Clock select

#define PINSEL0 (*(volatile unsigned int *)(0x4002C000))
#define PINSEL1 (*(volatile unsigned int *)(0x4002C004))
#define PINMODE0 (*(volatile unsigned int *)(0x4002C040))

#define T0TCR (*(volatile unsigned int *)(0x40004004)) 		// Timer 0
#define T0TC (*(volatile unsigned int *)(0x40004008))		// Timer Counter

#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)
#define FIO2PIN0 (*(volatile unsigned char *)0x2009C054)

#define T2TCR (*(volatile unsigned int *)(0x40090004)) 		// Timer 2 Timer Control Register
#define T2TC (*(volatile unsigned int *)(0x40090008)) 		// Timer 2 Timer Counter
#define T2EMR (*(volatile unsigned int *)(0x4009003C)) 		// EMR Match Register for Timer 2
#define T2MCR (*(volatile unsigned int *)(0x40090014)) 		// MCR Match Register for Timer 2
#define T2CTCR (*(volatile unsigned int *)(0x40090070)) 	// Count Control Register for Timer 2 Selects between timer and counter mode
#define T2MR3 (*(volatile unsigned int *)(0x40090024)) 		// Match Register 3

#define DACR (*(volatile unsigned int *)(0x4008C000)) 		// DAC Register

// UART0 for MIDI
#define U0LCR (*(volatile unsigned int *)(0x4000C00C))
#define U0DLL (*(volatile unsigned int *)(0x4000C000))
#define U0DLM (*(volatile unsigned int *)(0x4000C004))
#define U0FDR (*(volatile unsigned int *)(0x4000C028))
#define U0FCR (*(volatile unsigned int *)(0x4000C008))
#define U0ACR (*(volatile unsigned int *)(0x4000C020))
#define U0RBR (*(volatile unsigned int *)(0x4000C000))
#define U0LSR (*(volatile unsigned int *)(0x4000C014))

//** LCD Display is wired to our LPC as follows:
//** DB0-DB7 -> pins 42-49
//** E (Enable) -> pin 50 (p2.8)
//** Rs (data/instruction) -> pin 52 (p2.11)

// Configure MIDI Keyboard for inputs

// Configure GPIO pins for output to write to LCD display

struct _MIDIData {
	int key;
	int velocity;
	int flag;
};

typedef struct _MIDIData MIDIData; //defining struct type

MIDIData receivedData[8];


void GPIOInit() {
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
	while (timer0Read_us() < 500000.0) {
		int aout = (1 - (timer0Read_us() / 500000.0)) * 1023.0;
		DACR = aout << 6;
	}
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
	FIO2PIN |= (1 << 11); // Set Rs = 1 for character (bit 11 goes high)
	FIO2PIN0 = data; // set up DB0 - DB7 for ASCII codes for characters
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

void displayChar(int data) {
	FIO2PIN0 = data;
	FIO2PIN |= (1 << 11); //set Rs high
	FIO2PIN |= (1 << 8); // pulse E high
	FIO2PIN &= ~(1 << 8); // pulse E low
	wait_us(100); // wait 100 usec
}

//*** NEED TO CREATE A 3RD FUNCTION SIMILAR TO THOSE ABOVE TO TAKE IN A STRING AND DISPLAY ALL CHARACTERS***

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



int main(void) {
	PINSEL1 |= (1 << 21); 	// enable AOUT pin 18
	PINSEL1 &= ~(1 << 20);	// enable AOUT pin 18
	// initialize timers
	timer0Init();
	timer2Init();

	/*GPIOInit();
	 timer0Init();
	 //LCDinitCmd();
	 LCDinitChar();
	 displayChar(0x46);
	 displayChar(0x21);*/

	configMIDI(); // configure MIDI keyboard
	wait_us(100);

	while (1) {
		U0LCR &= ~(1 << 7); // must be zero to access RBR
		playMIDIByte(U0RBR); // read buffer register bytes into function
		//configT2MR3(550);
	}
	return 0;
}

