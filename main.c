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

#include "registerDef.h"
#include "final.h"

int cmpfunc(const void * a, const void * b) {
	return (*(int*) a - *(int*) b);
}

/*
 * Integer comparison: returns negative if b > a and positive if a > b
 */
int int_cmp(const void *a, const void *b) {
	const int *ia = (const int *) a; // casting pointer types
	const int *ib = (const int *) b;
	return *ia - *ib;
}

// qsort struct comparison function
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

	I2CInit();

	lcdInit();
	LCDinitChar();

	keypadInit();

	configMIDI();

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

	int data[8];
	
	/*
	 * Test welcome display
	 */
	welcomeDisp();

	while (1) {

		/*
		 * Test options display
		 */
		options1Disp();
		options2Disp();
		
		/*
		 * Check for keypad presses
		 */
		keyScan();
		
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
