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
		timer1Reset();
		timer1Start();
		if (((U0LSR >> 0) & 1) == 1) {

			data[0] = U0RBR;
			data[1] = U0RBR;
			data[2] = U0RBR;
			data[3] = U0RBR;
			data[4] = U0RBR;
			data[5] = U0RBR;
			data[6] = U0RBR;
			data[7] = U0RBR;

			if (keypad[1][0] == 1) {
				recordSquareWF(data);
			}
			else if (keypad[1][1] == 1) {
				recordTriangleWF(data);
			}

		}
		timer1Stop();
		noteLength[count] = 20000 * timer1Read_us();
//		else if (keypad[0][2] == 1) {
//			playSineWF(data);
//		}
	}
	configT2MR3(0);
	timer3Stop();
}

/*
 * Play back recorded song
 */
extern void playbackOpt(void) {
	// TODO playback function will probably come from EEPROM
	playback2Disp();
	if (keypad[1][0] == 1) {
		for (int i = 0; i < 25; i++) {
			if (receivedData[i] == 0x3c) {
				configT2MR3(259);		// play middle c (C4)
				wait1_us(noteLength[i]);
				configT2MR3(0);
			} else if (receivedData[i] == 0x3e) {
				configT2MR3(291);		// play D4
				wait1_us(noteLength[i]);
				configT2MR3(0);
			} else if (receivedData[i] == 0x40) {
				configT2MR3(327);		// play E4
				wait1_us(noteLength[i]);
				configT2MR3(0);
			} else if (receivedData[i] == 0x41) {
				configT2MR3(347);		// play F4
				wait1_us(noteLength[i]);
				configT2MR3(0);
			} else if (receivedData[i] == 0x43) {
				configT2MR3(389);		// play G4
				wait1_us(noteLength[i]);
				configT2MR3(0);
			} else if (receivedData[i] == 0x45) {
				configT2MR3(437);		// play A4
				wait1_us(noteLength[i]);
				configT2MR3(0);
			} else if (receivedData[i] == 0x47) {
				configT2MR3(490);		// play B4
				wait1_us(noteLength[i]);
				configT2MR3(0);
			} else if (receivedData[i] == 0x48) {
				configT2MR3(519);		// play C5 (full octave)
				wait1_us(noteLength[i]);
				configT2MR3(0);
			}
		}
		configT2MR3(0);
	}
	if (keypad[1][1] == 1) {
		for (int i = 0; i < 25; i++) {
			if (receivedData[i] == 0x3c) {
				triangleWave(700, 35);		// play middle c (C4)
				wait1_us(noteLength[i]);
				triangleWave(0, 0);
			} else if (receivedData[i] == 0x3e) {
				triangleWave(700, 40);		// play D4
				wait1_us(noteLength[i]);
				triangleWave(0, 0);
			} else if (receivedData[i] == 0x40) {
				triangleWave(700, 45);		// play E4
				wait1_us(noteLength[i]);
				triangleWave(0, 0);
			} else if (receivedData[i] == 0x41) {
				triangleWave(700, 47);		// play F4
				wait1_us(noteLength[i]);
				triangleWave(0, 0);
			} else if (receivedData[i] == 0x43) {
				triangleWave(700, 55);		// play G4
				wait1_us(noteLength[i]);
				triangleWave(0, 0);
			} else if (receivedData[i] == 0x45) {
				triangleWave(700, 60);		// play A4
				wait1_us(noteLength[i]);
				triangleWave(0, 0);
//		} else if (receivedData[i] == 0x47) {
//			configT2MR3(490);		// play B4
//			wait1_us(noteLength[i]);
			} else if (receivedData[i] == 0x48) {
				triangleWave(700, 75);		// play C5 (full octave)
				wait1_us(noteLength[i]);
				triangleWave(0, 0);
			}
		}
	}
	memset(keypad, 0, sizeof(keypad));
}

/*
 * Delete recorded song
 */
extern void deleteOpt(void) {
// TODO delete function will probably come from EEPROM
	memset(receivedData, 0, sizeof(receivedData));
	memset(noteLength, 0, sizeof(noteLength));
}

/*
 * Reset editor
 */
extern void resetOpt(void) {
// TODO reset function
}

/*
 * This is the initial routine the user sees before the edit takes place
 */
extern void preRecordingRoutine(void) {
	keypad[0][0] = 1;
	record1Disp();
	wait_us(5000000);

	wave1Prompt();
	wait_us(2000000);
	wave2Prompt();
	while (keypad[1][0] == 0 && keypad[1][1] == 0 && keypad[1][2] == 0) {
		checkRow2();
	}

	wait_us(2000000);

	click1Prompt();
	wait_us(2000000);
	click2Prompt();
	while (keypad[2][0] == 0 && keypad[2][1] == 0 && keypad[2][2] == 0
			&& keypad[2][3] == 0) {
		checkRow3();
	}

	wait_us(2000000);
}

/*
 * This is the routine the user sees just after the recording has occurred
 */
extern void postRecordingRoutine(void) {
	editor1Prompt();
	wait_us(2000000);
	editor2Prompt();
	while (keypad[0][1] == 0 && keypad[0][2] == 0) {
		checkRow1();
		if (keypad[0][1] == 0 && keypad[0][2] == 0) {
			checkRow4();
		}
	}
}
