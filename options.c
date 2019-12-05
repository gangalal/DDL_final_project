#include "final.h"

int data[8];
int count = 0;

/*
 * Record data from MIDI keyboard
 */
extern void recordOpt(void) {
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

			recordSquareWF(data);

		}
		timer1Stop();
		noteLength[count] = 6500 * timer1Read_us();

	}
	configT2MR3(0);
	timer3Stop();
}

/*
 * Play back recorded song
 */
extern void playbackOpt(void) {
	// TODO playback function will probably come from EEPROM
	playbackDisp();
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
	editorDisp();
	wait_us(2000000);
	postRecPrompt();
}

void playChordsOpt() {
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
extern void saveOpt() {

}
/*
 * Delete recorded song
 */
extern void editOpt(void) {
// TODO delete function will probably come from EEPROM
	memset(receivedData, 0, sizeof(receivedData));
	memset(noteLength, 0, sizeof(noteLength));
	keypad[0][0] = 1;
	keypad[2][0] = 1;
}

/*
 * Reset editor
 */
extern void resetOpt(void) {
// TODO reset function
	memset(receivedData, 0, sizeof(receivedData));
	memset(noteLength, 0, sizeof(noteLength));
	memset(keypad, 0, sizeof(keypad));
}


/*
 * This is the initial routine the user sees before the edit takes place
 */
extern void initialRoutine(void) {
	editorDisp();
	wait_us(2000000);
	initialPrompt();
	wait_us(2000000);
	while (keypad[2][0] == 0 && keypad[2][1] == 0) {
		checkRow3();
	}
	wait_us(2000000);
}

extern void preRecordingRoutine(void) {
	memset(keypad[1], 0, sizeof(keypad[1]));
	memset(keypad[2], 0, sizeof(keypad[2]));
	if (keypad[0][2] == 1) {
		keypad[0][2] = 0;
	}
	record1Disp();
	wait_us(2000000);

	click1Disp();
	wait_us(2000000);
	click1Prompt();
	while (keypad[1][0] == 0 && keypad[1][1] == 0 && keypad[1][2] == 0) {
		checkRow2();
	}
	wait_us(2000000);
}

/*
 * This is the routine the user sees just after the recording has occurred
 */
extern void postRecordingRoutine(void) {
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
