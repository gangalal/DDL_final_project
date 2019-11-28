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
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "Util.h"
#include "registerDef.h"
#include "timer.h"
#include "match2.h"
#include "timer3.h"
#include "midi.h"

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
// Configure LCD Instruction for commands
void LCDCmd(int data) {
	FIO2PIN &= ~(1 << 11); // Set Rs = 0 for cmd (clear bit 11)
	FIO2PIN0 = data; // set up DB0 - DB7
	FIO2PIN |= (1 << 8); // pulse E high
	FIO2PIN &= ~(1 << 8); // pulse E low
	wait_us(100); // wait 100 usec
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

void displayWords(int* array, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		displayChar(array[i]);
	}
	if (arraySize < 20) {
		for (int i = 0; i < (20 - arraySize); i++) {
			displayChar(0x20);
		}
	}
	//if (arraySize > 20 && arraySize < )
}

int waveform[] = { 0x43, 0x68, 0x6f, 0x6f, 0x73, 0x65, 0x20, 0x77, 0x61, 0x76,
		0x65, 0x66, 0x6f, 0x72, 0x6d };
int waveLen = size(waveform);
int triangle[] = { 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E,
		0x5E, 0x5E };
int triangleLen = size(triangle);
int sine[] = { 0x42, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E, 0x5E };
int sineLen = size(sine);

/*void wait_ticks(unsigned long count) {
 volatile int ticks;
 for (ticks = 0; ticks < count; ticks++) {

 }

 }

 for (int i = 0; i < 300; i=i+9) {
 DACR = i << 6;
 wait_ticks(10);
 }
 for (int i = 300; i >0; i=i-9) {
 DACR = i << 6;
 wait_ticks(10);
 }*/

int cmpfunc(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

int int_cmp(const void *a, const void *b) {
	const int *ia = (const int *) a; // casting pointer types
	const int *ib = (const int *) b;
	return *ia - *ib;
	/* integer comparison: returns negative if b > a
	 and positive if a > b */
}

// qsort struct comparision function
int struct_cmp_by_order(const void *a, const void *b) {
	MIDIData *ia = (MIDIData *) a;
	MIDIData *ib = (MIDIData *) b;
	return (int) (ia->order - ib->order);
}

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

	receivedData[0].order = 4;
	receivedData[1].order = 3;
	receivedData[2].order = 9;
	receivedData[3].order = 1;
	receivedData[4].order = 20;
	receivedData[5].order = 10;

	qsort(receivedData, 6, sizeof(MIDIData), struct_cmp_by_order);

	/*for (int i = 0; i < 6; i++)
	 printf("%d\n", receivedData[i].order);
	 */
	//U0LCR &= ~(1<<7);
	configT2MR3(0);
	configMIDI();

	int data[8];

	while (1) {
		/*timer0Start();
		 for (int i = 0; i < 300; i=i+5) {
		 DACR = i << 6;
		 wait_ticks(300);
		 DACR = 0;
		 wait_ticks(300);
		 }
		 timer0Stop();
		 printf("%d\n", timer0Read_us());
		 timer0Reset();*/
		//debug();
		U0LCR &= ~(1 << 7); // must be zero to access RBR

		if (((U0LSR >> 0) & 1) == 1) {

			data[0] = U0RBR;
			data[1] = U0RBR;
			data[2] = U0RBR;
			data[3] = U0RBR;
			data[4] = U0RBR;
			data[5] = U0RBR;
			data[6] = U0RBR;
			data[7] = U0RBR;

			for (int i = 0; i < 8; i++) {
				printf("%x  ", data[i]);
			}
			printf("\n......\n");

			//check(data);
			//printf("%x\n", U0RBR);

			//readMIDIByte(U0RBR); // read buffer register bytes into function

			//printf("%d\n", timer0Read_us());
			//printf("Count is: %d\n", count);
		}
	}
	return 0;
}

