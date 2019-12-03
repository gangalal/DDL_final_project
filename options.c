#include "final.h"

/*
 *
 */
extern void beginningRoutine(void) {
	editor2Prompt();
	while (keypad[0][0] == 0 && keypad[0][1] == 0 && keypad[0][2] == 0) {
		checkRow1();
	}
	wave2Prompt();
	while (keypad[1][0] == 0 && keypad[1][1] == 0 && keypad[1][2] == 0) {
		checkRow2();
	}
	click2Prompt();
	while (keypad[2][0] == 0 && keypad[2][1] == 0 && keypad[2][2] == 0 && keypad[2][3] == 0) {
		checkRow3();
		if (keypad[2][0] == 1 || keypad[2][1] == 1 || keypad[2][2] == 1 || keypad[2][3] == 1) {
			break;
		}
	}
}
/*
 * Functions for selected options
 */
extern void recordOpt(void) {
	// TODO record function will probably come from EEPROM
}

extern void playbackOpt(void){
	// TODO playback function will probably come from EEPROM
}

extern void deleteOpt(void) {
	// TODO delete function will probably come from EEPROM
}

extern void resetOpt(void) {
	// TODO reset function
}
