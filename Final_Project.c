/*
 ===============================================================================
 Name        : FinalProject.c
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

#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)
#define FIO2PIN0 (*(volatile unsigned char *)0x2009c054) // define register for Port 2 for DB0-DB7 writing

//** LCD Display is wired to our LPC as follows:
//** DB0-DB7 -> pins 42-49
//** E (Enable) -> pin 50 (p2.8)
//** Rs (data/instruction) -> pin 52 (p2.11)


// Configure GPIO pins for output to write to LCD display
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

// Configure LCD Instruction for commands
void LCDCmd (int data) {
	FIO2PIN &= ~(1 << 11); // Set Rs = 0 for cmd (clear bit 11)
	FIO2PIN0 = data; // set up DB0 - DB7
	FIO2PIN |= (1 << 8); // pulse E high
	FIO2PIN &= ~(1 << 8); // pulse E low
	wait_us(100); // wait 100 usec
}

// Initialize LCD (COMMANDS) ** optional can call from main as well
void LCDinitCmd (void) {
	LCDCmd(0x38); // Function Set
	LCDCmd(0x0E); // Turn display on, cursor on, no cursor blinking
	LCDCmd(0x06); // Entry mode cmd, cursor move L to R
	LCDCmd(0x01); // clear display
	wait_us(4000); // wait 4ms to clear display
}

// Configure LCD Instruction for Characters
void LCDchar (int data) {
	FIO2PIN |= (1 << 11); // Set Rs = 1 for character (bit 11 goes high)
	FIO2PIN0 = data; // set up DB0 - DB7 for ASCII codes for characters
	FIO2PIN |= (1 << 8); // pulse E high
	FIO2PIN &= ~(1 << 8); // pulse E low
	wait_us(100); // wait 100 usec
}

// Initialize LCD (CHARACTERS) ** optional can call from main as well
void LCDinitChar (void) {
	LCDCmd(0x38); // Function Set
	LCDCmd(0x0E); // Turn display on, cursor on, no cursor blinking
	LCDCmd(0x06); // Entry mode cmd, cursor move L to R
	LCDCmd(0x01); // clear display
	wait_us(4000); // wait 4ms to clear display
}

//*** NEED TO CREATE A 3RD FUNCTION SIMILAR TO THOSE ABOVE TO TAKE IN A STRING AND DISPLAY ALL CHARACTERS***


void sendInit() {
	FIO2PIN |= (0 << 0);
	FIO2PIN |= (0 << 1);
	FIO2PIN |= (1 << 2);
	FIO2PIN |= (1 << 3);
	FIO2PIN |= (1 << 4);
	FIO2PIN |= (0 << 5);
	FIO2PIN |= (0 << 6);
	FIO2PIN |= (0 << 7);
	FIO2PIN |= (1 << 11); //Rs 1
}

void sendComand() {
	FIO2PIN |= (0 << 0);
	FIO2PIN |= (0 << 1);
	FIO2PIN |= (0 << 2);
	FIO2PIN |= (0 << 3);
	FIO2PIN |= (0 << 4);
	FIO2PIN |= (0 << 5);
	FIO2PIN |= (0 << 6);
	FIO2PIN |= (1 << 7);
	FIO2PIN &= ~(1 << 11); //Rs low
}

int main(void) {
	GPIOInit();
	sendInit();
	wait_us(100);
	sendComand();
	FIO2PIN |= (1 << 8); //E high
	FIO2PIN &= ~(1 << 8); // E low
	wait_us(100);
	while (1) {
    printf("hello world\n");
	}
	return 0;
}
