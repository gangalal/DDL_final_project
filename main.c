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

void playEditedData() {
	for (int i = 0; i < sizeof(receivedData); i++) {
		configT2MR3(receivedData[i]);
	}
}

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

	/*
	 * Test welcome display
	 */
	welcomeDisp();
	waitOneSecond(5);
	configT2MR3(0);

	while (1) {
//		fillWaveTable();

		while (keypad[0][0] == 0 && keypad[0][1] == 0 && keypad[0][2] == 0) {
			/*
			 *
			 */
			preRecordingRoutine();
		}

		/*
		 * Choose click track based on user selection from pre-recording routine
		 */
		if (keypad[2][0] == 1) {
			configT3MR0(2);
		}
		else if (keypad[2][1] == 1) {
			configT3MR0(3);
		}
		else if (keypad[2][2] == 1) {
			configT3MR0(4);
		}
		else {
			timer3Stop();
		}

		/*
		 * record song
		 */
		recordOpt();

		/*
		 * User can select playback or edit
		 */
		checkRow1();
	}

	return 0;
}
