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


