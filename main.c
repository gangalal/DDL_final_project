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



int main(void) {
	PINSEL1 = (1 << 21) | (0 << 20); 	// enable AOUT pins

	timer0Init();
	timer2Init();
	timer3Init();
	timer3Stop();

	I2CInit();

	lcdInit();
	LCDinitChar();

	keypadInit();

	configMIDI();

	U0LCR &= ~(1 << 7);

	int data[8];

	/*
	 * Test welcome display
	 */
	welcomeDisp();
	waitOneSecond(5);

	while (1) {
//		fillWaveTable();

		/*
		 * Present the user with editor options
		 */
		beginningRoutine();

		/*
		 * Choose click track based on user selection from beginning routine
		 */
		if (keypad[2][0] == 1) {
			configT3MR0(2);
		} else if (keypad[2][1] == 1) {
			configT3MR0(3);
		} else if (keypad[2][2] == 1) {
			configT3MR0(4);
		} else {
			timer3Stop();
		}

		/*
		 * Continuously scan the keys through the while loop - may change
		 */
//		keyScan();

		U0LCR &= ~(1 << 7); // must be zero to access RBR
		if (count < 25){
		if (((U0LSR >> 0) & 1) == 1) {

			data[0] = U0RBR;
			data[1] = U0RBR;
			data[2] = U0RBR;
			data[3] = U0RBR;
			data[4] = U0RBR;
			data[5] = U0RBR;
			data[6] = U0RBR;
			data[7] = U0RBR;


			if (keypad[2][0] == 1) {
				playSquareWF(data);

			}
			else if (keypad[2][1] == 1) {
				playTriangleWF(data);
			}
//			else if (keypad[2][2] == 1) {
//				playSineWF(data);
//			}

		}
		}
		for (int i = 0;i<25;i++)
			printf("Byte: %x\n", receivedData[i]);
	}
	return 0;
}
