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
	timer2Stop();
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
	wait_us(5000000);

	//configT2Chord(0,0);

	while (1) {

		// begin initial routine
		checkRow3();

		// select click track
		checkRow2();

		// play click track based on user selection from pre-recording routine
		if (keypad[1][0] == 1) {
			configT3MR0(2);
		} else if (keypad[1][1] == 1) {
			configT3MR0(3);
		} else if (keypad[1][2] == 1) {
			configT3MR0(4);
		} else {
			timer3Stop();
		}

		// record song; reset keypad selections
		recordOpt();

		// User can select playback, save, edit, or reset
		checkRow1();
	}

	return 0;
}
