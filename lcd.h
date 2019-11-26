/*
 ===============================================================================
 Name        : lcd.h
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
#include <math.h>
#include "Util.h"
#include "timer.h"

/*
 * Initialize GPIO2 pins as outputs and set them low
 */
void lcdInit() {
	FIO2DIR |= (1 << 0); // configure P2[0] as output
	FIO2DIR |= (1 << 1);
	FIO2DIR |= (1 << 2);
	FIO2DIR |= (1 << 3);
	FIO2DIR |= (1 << 4);
	FIO2DIR |= (1 << 5);
	FIO2DIR |= (1 << 6);
	FIO2DIR |= (1 << 7);
	FIO2DIR |= (1 << 8);
	FIO2DIR |= (1 << 11);

	FIO2PIN &= ~(1 << 0); //set P2[0] low
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
