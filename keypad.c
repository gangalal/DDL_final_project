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
	memset(keypad,0,sizeof(keypad));

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
 * Row 1 corresponds to main editor options: Record, Playback, Delete
 */
void checkRow1(void) {

	setRow1();
	wait_us(250);

	editor1Prompt();
	wait_us(5000000);
	editor2Prompt();

	if (((FIO0PIN >> 17) & 0x01) == 1) {
		if (keypad[0][0] == 0) {
			playbackDisp();
			playbackOpt();	// TODO make playbackOpt() EEPROMsaveDisp();
			memset(keypad[0],0,sizeof(keypad[0]));
			keypad[0][0] = 1;
		}
		wait_us(50000);
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		if (keypad[0][1]) {
			saveDisp();
			saveOpt();		// TODO make a saveOpt() EEPROM
			memset(keypad[0],0,sizeof(keypad[0]));
			keypad[0][1] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 16) & 0x01) == 1) {
		if(keypad[0][2]) {
			editDisp();
			deleteOpt();	// TODO make deleteOpt() EEPROM
			memset(keypad[0],0,sizeof(keypad[0]));
			keypad[0][2] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf("You have pressed A.\n");
		wait_us(50000);
	}

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

	setRow2();
	wait_us(250);

	if (((FIO0PIN >> 17) & 0x01) == 1) {
		if (keypad[1][0] == 0) {
			slowClickDisp();
			memset(keypad[1],0,sizeof(keypad[1]));
			keypad[1][0] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 15) & 0x01) == 1) {
		if (keypad[1][1] == 0) {
			normalClickDisp();
			memset(keypad[1],0,sizeof(keypad[1]));
			keypad[1][1] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 16) & 0x01) == 1) {
		if (keypad[1][2] == 0) {
			fastClickDisp();
			memset(keypad[1],0,sizeof(keypad[1]));
			keypad[1][2] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 23) & 0x01) == 1) {
		if (keypad[1][3] == 0) {
			noClickDisp();
			memset(keypad[2],0,sizeof(keypad[2]));
		}
		wait_us(50000);
	}

	wait_us(50000);
	rowReset();
	wait_us(250);

}

/*
 * Row 3 of the keypad corresponds to click track speed selection: slow, normal, fast
 */
void checkRow3(void) {

	setRow3();
	wait_us(250);

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
			if (keypad[2][0] == 0) {

			memset(keypad[2],0,sizeof(keypad[2]));
			keypad[2][0] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 15) & 0x01) == 1) {
		if (keypad[2][1] == 0) {

			memset(keypad[2],0,sizeof(keypad[2]));
			keypad[2][1] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 16) & 0x01) == 1) {
		if (keypad[2][2] == 0) {

			memset(keypad[2],0,sizeof(keypad[2]));
			keypad[2][2] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 23) & 0x01) == 1) {
		if (keypad[2][3] == 0) {

			memset(keypad[2],0,sizeof(keypad[2]));
			keypad[2][3] = 1;
		}
		wait_us(50000);
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

/*
 * Scan for pressed key
 * We can combine the checkRow functions if we want to - kept it separate until
 * we determine which rows we will be using. This will depend on how many
 * functions we end up needing to use on the keypad.
 */
void keyScan(void) {

	checkRow1();
	checkRow2();
	checkRow3();
	checkRow4();

}
