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
#include "registerDef.h"
#include "Util.h"
#include "timer.h"
#include "match2.h"


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



int main(void) {
	PINSEL1 &= ~(1 << 20);
	PINSEL1 |= (1 << 21);	// enable AOUT pins
	configMIDI();

	while (1) {
		U0LCR &= ~(1 << 7); // must be zero to access RBR
		if (U0RBR == 0x3c) {
			printf("Note on! %x\n", U0RBR);
			configT2MR3(261);
		}


		}
	return 0;
}
