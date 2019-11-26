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
#include "registerDef.h"
#include "timer.h"
#include "match2.h"
#include "timer3.h"


void GPIOInit() {
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
 FIO2PIN &= ~(1 << 8); //for E
 FIO2PIN &= ~(1 << 11); //for Rs
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

 //*** NEED TO CREATE A 3RD FUNCTION SIMILAR TO THOSE ABOVE TO TAKE IN A STRING AND DISPLAY ALL CHARACTERS***

 void displayChar(int data) {
 FIO2PIN0 = data;
 FIO2PIN |= (1 << 11); //set Rs high
 FIO2PIN |= (1 << 8); // pulse E high
 FIO2PIN &= ~(1 << 8); // pulse E low
 wait_us(100); // wait 100 usec
 }

 void displayWords(int* array, int arraySize)
 {
	 for(int i = 0; i<arraySize; i++)
	 {
		 displayChar(array[i]);
	 }
	 if (arraySize<20)
	 {
		 for(int i = 0; i <(20-arraySize); i++)
		 {
			 displayChar(0x20);
		 }
	 }
 }

void configMIDI() {
	PCONP |= (1 << 3); //on reset UART is enable
	PCLKSEL0 |= (0 << 6) | (0 << 7);
	U0LCR |= (1 << 7); //DLAB = 1 enable DLAB
	PINSEL0 |= (0 << 5) | (1 << 4);
	PINSEL0 |= (0 << 7) | (1 << 6);
	//skipped interrupts
	U0FCR |= (1 << 2); // will clear all bytes in RX FIFO
	U0FCR |= (1 << 2); // will clear all bytes in TX FIFO
	U0DLL = 0; // determines the Baud rate
	U0DLM = 2;
	U0TER |= (1 << 7); //data written to the THR is output on the TXD pin
}

int waveform [] = {0x43, 0x68, 0x6f, 0x6f, 0x73, 0x65, 0x20, 0x77, 0x61, 0x76, 0x65, 0x66, 0x6f, 0x72, 0x6d};
int waveLen = size(waveform);
int triangle [] = {0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E};
int triangleLen = size(triangle);
int sine [] = {0x42, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E};
int sineLen = size(sine);


int main(void) {
	PINSEL1 = (1 << 21) | (0 << 20); 	// enable AOUT pins
	timer0Init();
	timer2Init();
	timer3Init();

	 GPIOInit();
	 LCDinitChar();
	 displayWords(waveform, waveLen);
	 displayWords(triangle, triangleLen);
	 displayWords(sine, sineLen);
	//configMIDI();
	while (1) {
		configT3MR0(550);
		configT2MR3(550);
		debug();
	}
	return 0;
}


