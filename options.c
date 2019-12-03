#include "final.h"

int data[8];
int count = 0;

/*
 * Record data from MIDI keyboard
 */
extern void recordOpt(void) {
	// TODO record function will probably come from EEPROM
	record2Disp();
	U0LCR &= ~(1 << 7); // must be zero to access RBR
	while (count < 25) {
		if (((U0LSR >> 0) & 1) == 1) {

			data[0] = U0RBR;
			data[1] = U0RBR;
			data[2] = U0RBR;
			data[3] = U0RBR;
			data[4] = U0RBR;
			data[5] = U0RBR;
			data[6] = U0RBR;
			data[7] = U0RBR;
			recordSquareWF(data);

		}
//		else if (keypad[0][1] == 1) {
//			recordTriangleWF(data);
//		}
//		else if (keypad[0][2] == 1) {
//			playSineWF(data);
//		}

	}
}
/*
 *
 */
extern void preRecordingRoutine(void) {
	wave1Prompt();
	wait_us(5000000);
	wave2Prompt();
	while (keypad[1][0] == 0 && keypad[1][1] == 0 && keypad[1][2] == 0) {
		checkRow2();
	}
	click1Prompt();
	wait_us(5000000);
	click2Prompt();
	while (keypad[2][0] == 0 && keypad[2][1] == 0 && keypad[2][2] == 0
			&& keypad[2][3] == 0) {
		checkRow3();
		if (keypad[2][0] == 1 || keypad[2][1] == 1 || keypad[2][2] == 1
				|| keypad[2][3] == 1) {
			break;
		}
	}
}

extern void playbackOpt(void) {
	// TODO playback function will probably come from EEPROM
	playbackDisp();
	for (int i = 0; i < sizeof(receivedData); i++) {
		configT2MR3(receivedData[i]);
	}
}

extern void deleteOpt(void) {
// TODO delete function will probably come from EEPROM
}

extern void resetOpt(void) {
// TODO reset function
}
