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
	PCLKSEL0 |= (0 << 6) | (0 << 7);
	U0LCR = (1 << 7); //DLAB = 1 enable DLAB
	PINSEL0 |= (0 << 5) | (1 << 4);
	PINSEL0 |= (0 << 7) | (1 << 6);
	//skipped interrupts
	U0DLL = 0;
	U0DLM = 2;
}



int main(void) {
	configMIDI();
	PINSEL1 = (1 << 21) | (0 << 20); 	// enable AOUT pins
	while (1) {
		printf("hello world\n");

	}
	return 0;
}
