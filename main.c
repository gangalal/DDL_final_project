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
#define PINMODE1 (*(volatile unsigned int *)(0x4002c044))

#define T0TCR (*(volatile unsigned int *)(0x40004004)) 		// Timer 0
#define T0TC (*(volatile unsigned int *)(0x40004008))		// Timer Counter

#define FIO0DIR (*(volatile unsigned int *)(0x2009c000))
#define FIO0PIN (*(volatile unsigned int *)(0x2009c014))
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

/* LCD Display is wired to our LPC as follows:
 * DB0-DB7 -> pins 42-49
 * E (Enable) -> pin 50 (p2.8)
 * Rs (data/instruction) -> pin 52 (p2.11)
 */

// Configure MIDI Keyboard for inputs

// Configure GPIO pins for output to write to LCD display

struct _MIDIData {
	int key;
	int velocity;
	int flag;
};

typedef struct _MIDIData MIDIData; //defining struct type

MIDIData receivedData[8];

/*
 * Configure MIDI Keyboard for inputs and
 * Configure GPIO pins for output to write to LCD display
 */
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

	/*
	 * Set all pins low initially
	 */
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

/*
 * Configure LCD Instruction for commands
 */
void LCDCmd(int data) {
	FIO2PIN &= ~(1 << 11); // Set Rs = 0 for cmd (clear bit 11)
	FIO2PIN0 = data; // set up DB0 - DB7
	FIO2PIN |= (1 << 8); // pulse E high
	FIO2PIN &= ~(1 << 8); // pulse E low
	wait_us(100); // wait 100 usec
}

/*
 * Initialize LCD (COMMANDS) ** optional can call from main as well
 */
void LCDinitCmd(void) {
	LCDCmd(0x38);	// Function Set
	LCDCmd(0x0E);	// Turn display on, cursor on, no cursor blinking
	LCDCmd(0x06);	// Entry mode cmd, cursor move L to R
	LCDCmd(0x01);	// clear display
	wait_us(4000);	// wait 4ms to clear display
}

/*
 * Configure LCD Instruction for Characters
 */
void LCDchar(int data) {
	FIO2PIN |= (1 << 11); // Set Rs = 1 for character (bit 11 goes high)
	FIO2PIN0 = data; // set up DB0 - DB7 for ASCII codes for characters
	FIO2PIN |= (1 << 8); // pulse E high
	FIO2PIN &= ~(1 << 8); // pulse E low
	wait_us(100); // wait 100 usec
}

/*
 * Initialize LCD (CHARACTERS) ** optional can call from main as well
 */
void LCDinitChar(void) {
	LCDCmd(0x38);	// Function Set
	LCDCmd(0x0E);	// Turn display on, cursor on, no cursor blinking
	LCDCmd(0x06);	// Entry mode cmd, cursor move L to R
	LCDCmd(0x01);	// clear display
	wait_us(4000);	// wait 4ms to clear display
}

/*
 *
 */
void displayChar(int data) {
	FIO2PIN0 = data;
	FIO2PIN |= (1 << 11); 	// set Rs high
	FIO2PIN |= (1 << 8); 	// pulse E high
	FIO2PIN &= ~(1 << 8); 	// pulse E low
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

/*
 * Initialize pins as inputs and outputs
 * Initialize pull-up/pull-down resistors
 * for the 4x4 keypad
 */
void initKeypadIO(void) {

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
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf("You have selected the triangle waveform.\n");
		wait_us(50000);
		// TODO input command for triangle waveform & LCD display info
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf("You have selected the sine waveform.\n");
		wait_us(50000);
		// TODO input command for sine waveform & LCD display info
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
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf("You have selected the normal click track speed.\n");
		wait_us(50000);
		// TODO input command for normal click track speed & LCD display info
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf("You have selected the high click track speed.\n");
		wait_us(50000);
		// TODO input command for high click track speed & LCD display info
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

	/*GPIOInit();
	 timer0Init();
	 //LCDinitCmd();
	 LCDinitChar();
	 displayChar(0x46);
	 displayChar(0x21);*/

	configMIDI(); 	// configure MIDI keyboard
	wait_us(100);
	
	initKeypadIO();	// configure 4x4 keypad
	wait_us(100);

	while (1) {

		keyScan();

		U0LCR &= ~(1 << 7); // must be zero to access RBR
		playMIDIByte(U0RBR); // read buffer register bytes into function
		//configT2MR3(550);
	}
	return 0;
}
