#include "final.h"

/*
 * If we use this method - we have to be CAREFUL with syntax!
 * keyTable[row][col]
 *
 * {{'1','2','3','A'},
 * {'4','5','6','B'},
 * {'7','8','9','C'},
 * {'*','0','#','D'}};
 *
 */
char keypad[4][4];

/*
 * Initialize GPIO0 pins as inputs and outputs
 * Initialize pull-up/pull-down resistors
 * for the 4x4 keypad
 */
void keypadInit(void) {

	/*
	 * Set pins 8-11 as outputs - "rows"
	 * Set pins 12-15 as inputs - "columns"
	 */
	FIO0DIR |= (1 << 6);	// Pin 8 	- 	Row 1
	FIO0DIR |= (1 << 0);	// Pin 9 	- 	Row 2
	FIO0DIR |= (1 << 1);	// Pin 10 	- 	Row 3
	FIO0DIR |= (1 << 18);	// Pin 11 	- 	Row 4
	FIO0DIR &= ~(1 << 17);	// Pin 12 	- 	Column 1
	FIO0DIR &= ~(1 << 15);	// Pin 13	-	Column 2
	FIO0DIR &= ~(1 << 16);	// Pin 14	-	Column 3
	FIO0DIR &= ~(1 << 23);	// Pin 15	-	Column 4

	/*
	 * Set pins 8-11 low
	 */
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);

	/*
	 * Set pins 12-15 with internal pull down resistors
	 * See the above question
	 */
	PINMODE1 |= (1 << 2) | (1 << 3);
	PINMODE0 |= (1 << 30) | (1 << 31);
	PINMODE1 |= (1 << 0) | (1 << 1);
	PINMODE1 |= (1 << 14) | (1 << 15);

	/*
	 * Initialize key table to zero
	 */
	memset(keypad, 0, sizeof(keypad));

}

/*
 * Reset Row 1 selections
 */
void resetRow1Sel(void) {
	memset(keypad[0], 0, sizeof(keypad[0]));
}

/*
 * Reset Row 2 selections
 */
void resetRow2Sel(void) {
	memset(keypad[1], 0, sizeof(keypad[1]));
}

/*
 * Reset Row 3 selections
 */
void resetRow3Sel(void) {
	memset(keypad[2], 0, sizeof(keypad[2]));
}

/*
 * Reset all selections
 */
void resetAllSel(void) {
	memset(keypad, 0, sizeof(keypad));
}

/*
 * Set pins 8-11 low
 */
void rowReset(void) {

	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);
	wait_us(250);

}

/*
 * Set Row 1 high, the rest low
 */
void setRow1(void) {

	FIO0PIN |= (1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);
	wait_us(250);

}

/*
 * Set Row 2 high, the rest low
 */
void setRow2(void) {

	FIO0PIN |= (1 << 0);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);
	wait_us(250);

}

/*
 * Set Row 3 high, the rest low
 */
void setRow3(void) {

	FIO0PIN |= (1 << 1);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 18);
	wait_us(250);

}

/*
 * Set Row 4 high, the rest low
 */
void setRow4(void) {

	FIO0PIN |= (1 << 18);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	wait_us(250);

}

/*
 * Row 1 corresponds to main editor options: Playback, Save, Edit, or Reset
 */
void checkRow1(void) {

	while (keypad[0][0] == 0 && keypad[0][1] == 0 && keypad[0][2] == 0) {
		editorDisp();
		wait_us(2000000);
		postRecPrompt();
		wait_us(2000000);

		setRow1();
		wait_us(250);

		// play current song
		if (((FIO0PIN >> 17) & 0x01) == 1) {
			if (keypad[0][0] == 0) {
				playbackOpt();
			}
			wait_us(50000);
		}

		// save current song to EEPROM
		if (((FIO0PIN >> 15) & 0x01) == 1) {
			if (keypad[0][1] == 0) {
				keypad[0][1] = 1;
				saveToMemOpt();

				wait_us(2000000);
				rowReset();
				setRow4();
				wait_us(250);

				playFromMemDisp();
				while (keypad[0][1] == 1) {
					if (((FIO0PIN >> 15) & 0x01) == 1) {
						playFromMemOpt();
						keypad[3][1] = 0;
					}
				}
			}
			wait_us(50000);

			// edit current song
		} else if (((FIO0PIN >> 16) & 0x01) == 1) {
			if (keypad[0][2] == 0) {
				editOpt();
				keypad[0][2] = 1;
				keypad[2][0] = 1;
				resetRow2Sel();
			}
		}
		// check for reset
		if (keypad[0][0] == 0 && keypad[0][1] == 0 && keypad[0][2] == 0) {
			checkRow4();
		}
	}
	resetRow1Sel();
	wait_us(50000);
	rowReset();
	wait_us(250);

}

/*
 * Row 2 of the keypad corresponds to waveform selection: square, triangle, sine
 *
 * The readMidiByte will need to check the status of this row to produce the right waveform.
 */
void checkRow2(void) {

	while (keypad[2][0] == 1 && keypad[1][0] == 0 && keypad[1][1] == 0
			&& keypad[1][2] == 0 && keypad[1][3] == 0) {
		clickDisp();
		wait_us(2000000);
		clickPrompt();
		wait_us(2000000);

		setRow2();
		wait_us(250);

		if (((FIO0PIN >> 17) & 0x01) == 1) {
			if (keypad[1][0] == 0) {
				slowClickDisp();
				wait_us(2000000);
				memset(keypad[1], 0, sizeof(keypad[1]));
				keypad[1][0] = 1;
			}
			wait_us(50000);
		} else if (((FIO0PIN >> 15) & 0x01) == 1) {
			if (keypad[1][1] == 0) {
				normalClickDisp();
				wait_us(2000000);
				memset(keypad[1], 0, sizeof(keypad[1]));
				keypad[1][1] = 1;
			}
			wait_us(50000);
		} else if (((FIO0PIN >> 16) & 0x01) == 1) {
			if (keypad[1][2] == 0) {
				fastClickDisp();
				wait_us(2000000);
				memset(keypad[1], 0, sizeof(keypad[1]));
				keypad[1][2] = 1;
			}
			wait_us(50000);
		} else if (((FIO0PIN >> 23) & 0x01) == 1) {
			if (keypad[1][3] == 0) {
				noClickDisp();
				wait_us(2000000);
				memset(keypad[2], 0, sizeof(keypad[2]));
				keypad[1][3] = 1;
			}
			wait_us(50000);
		}
	}

	wait_us(50000);
	rowReset();
	wait_us(250);

}

/*
 * Row 3 of the keypad corresponds to initial or post-reset options
 */
void checkRow3(void) {

	while (keypad[2][0] == 0 && keypad[2][1] == 0) {
		editorDisp();
		wait_us(2000000);
		initialPrompt();
		wait_us(2000000);
		setRow3();
		wait_us(250);

		// Record option
		if (((FIO0PIN >> 17) & 0x01) == 1) {
			if (keypad[2][0] == 0) {
				// Keep track of the fact that we are in recording mode
				keypad[2][0] = 1;
			}
			recordDisp();
			wait_us(2000000);
		}

		// Chord option
		else if (((FIO0PIN >> 15) & 0x01) == 1) {
			if (keypad[2][1] == 0) {
				// keep track of the fact that we are in chord playing mode
				keypad[2][1] = 1;
				playChordsOpt();
				resetAllSel();
			}
			wait_us(50000);
		} else if (((FIO0PIN >> 16) & 0x01) == 1) {
			if (keypad[2][2] == 0) {
				memset(keypad[2], 0, sizeof(keypad[2]));
				keypad[2][2] = 1;
			}
			wait_us(50000);
		} else if (((FIO0PIN >> 23) & 0x01) == 1) {
			if (keypad[2][3] == 0) {
				memset(keypad[2], 0, sizeof(keypad[2]));
				keypad[2][3] = 1;
			}
			wait_us(50000);
		}
	}

	wait_us(50000);
	rowReset();
	wait_us(250);
}

/*
 * Reset editor application by selecting "*"
 */
void checkRow4(void) {

	setRow4();
	wait_us(250);

	if (((FIO0PIN >> 17) & 0x01) == 1) {
		if (keypad[3][0] == 0) {
			resetOpt();
			timer3Stop();
			configT2MR3(0);
		}
		wait_us(50000);
	}
//	else if (((FIO0PIN >> 15) & 0x01) == 1) {
//		printf("You have pressed 0.\n");
//		wait_us(50000);
//	}
//	else if (((FIO0PIN >> 16) & 0x01) == 1) {
//		printf("You have pressed #.\n");
//		wait_us(50000);
//	}
//	else if (((FIO0PIN >> 23) & 0x01) == 1) {
//		printf("You have pressed D.\n");
//		wait_us(50000);
//	}

	wait_us(50000);
	rowReset();
	wait_us(250);

}
