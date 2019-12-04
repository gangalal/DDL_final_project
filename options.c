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
	configT2mr3(0);
	timer3Stop()
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
	for (int i = 0; i < 25; i++) {
		if (receivedData[i] == 0x3c) {
				configT2MR3(259);		// play middle c (C4)
		} else if (receivedData[i] == 0x3e) {
				configT2MR3(291);		// play D4
		} else if (receivedData[i] == 0x40) {
				configT2MR3(327);		// play E4
		} else if (receivedData[i] == 0x41) {
				configT2MR3(347);		// play F4
		} else if (receivedData[i] == 0x43) {
				configT2MR3(389);		// play G4
		} else if (receivedData[i] == 0x45) {
				configT2MR3(437);		// play A4
		} else if (receivedData[i] == 0x47) {
				configT2MR3(490);		// play B4
		} else if (receivedData[i] == 0x48) {
				configT2MR3(519);		// play C5 (full octave)
		}
	}
}

extern void deleteOpt(void) {
// TODO delete function will probably come from EEPROM
}

extern void resetOpt(void) {
// TODO reset function
}
