#include "final.h"

int data[8];
int count = 0;

/*
 * Record data from MIDI keyboard
 */
void recordOpt(void) {
	// only record when the record option has been selected
	while (keypad[2][0] == 1) {

		// recording initial song
		if (keypad[0][2] == 0) {
			recordPrompt();
		}
		// editing song
		else {
			editPrompt();
		}
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

				recordSquareWF(data);

			}
			timer1Stop();
			noteLength[count] = 6500 * timer1Read_us();

		}
		configT2MR3(0);
		timer3Stop();
		count = 0;
		// reset the record and edit option
		keypad[2][0] = 0;
		keypad[0][2] = 0;
	}
}

/*
 * Play back recorded song
 */
void playbackOpt(void) {
	// TODO playback function will probably come from EEPROM
	lovelySong();
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
	timer3Stop();
	keypad[0][0] = 0;
}

void playChordsOpt() {

	chordExitDisp();
	wait_us(2000000);

	int data[8];
	if (((U0LSR >> 0) & 1) == 1) {

		data[0] = U0RBR;
		data[1] = U0RBR;
		data[2] = U0RBR;
		data[3] = U0RBR;
		data[4] = U0RBR;
		data[5] = U0RBR;
		data[6] = U0RBR;
		data[7] = U0RBR;

		if (data[0] == 0x4a) {
			configT2MR3(259); // C4
			configT3MR0(389); //G4
		}
		if (data[0] == 0x4c) {
			configT2MR3(291); //D4
			configT3MR0(437); //A4
		}
		if (data[0] == 0x4d) {
			configT2MR3(347); //F4
			configT3MR0(519); //C5
		}
	}
	checkRow4();
}

/*
 * Save current song
 */
void saveOpt() {
}

/*
 * Delete recorded song
 */
void editOpt(void) {
	editDisp();
	memset(receivedData, 0, sizeof(receivedData));
	memset(noteLength, 0, sizeof(noteLength));
	count = 0;
}

/*
 * Reset editor
 */
void resetOpt(void) {
	resetDisp();
	resetAllSel();
	keypad[0][0] = 1;
	keypad[0][1] = 1;
	keypad[0][2] = 1;
	memset(receivedData, 0, sizeof(receivedData));
	memset(noteLength, 0, sizeof(noteLength));
	count = 0;
}

/*
 * This is the initial routine the user sees before the edit takes place
 */
void initialRoutine(void) {
	editorDisp();
	wait_us(2000000);
	initialPrompt();
	wait_us(2000000);
	while (keypad[2][0] == 0 && keypad[2][1] == 0) {
		checkRow3();
	}
	wait_us(2000000);
}

void preRecordingRoutine(void) {
	resetRow1Sel();
	resetRow2Sel();

	// if in editing mode
	if (keypad[0][2] == 0) {
		recordDisp();
		wait_us(2000000);
	}

	// otherwise...
	else if (keypad[0][2] == 1) {
		recordPrompt();
		wait_us(2000000);
	}

	clickDisp();
	wait_us(2000000);
	clickPrompt();
	while (keypad[1][0] == 0 && keypad[1][1] == 0 && keypad[1][2] == 0) {
		checkRow2();
	}
	wait_us(2000000);
}

/*
 * This is the routine the user sees just after the recording has occurred
 */
void postRecordingRoutine(void) {
	editorDisp();
	wait_us(2000000);
	postRecPrompt();
	while (keypad[0][0] == 0 && keypad[0][1] == 0 && keypad[0][2] == 0) {
		checkRow1();
		if (keypad[0][0] == 0 && keypad[0][1] == 0 && keypad[0][2] == 0) {
			checkRow4();
		}
	}
}
