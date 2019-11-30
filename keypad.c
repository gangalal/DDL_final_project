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
char otherKeyTable[4][4];
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
	memset(otherKeyTable,0,sizeof(otherKeyTable));

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
 * Determine if a key in Row 1 has been pressed and prints test statement
 */
void checkRow1(void) {

	setRow1();
	wait_us(250);

	/*
	 * Row 1 of the keypad corresponds to editor options
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		if (otherKeyTable[0][0] == 0) {
			recordDisp();
			recordOpt();
			memset(otherKeyTable[0],0,sizeof(otherKeyTable[0]));
			otherKeyTable[0][0] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 15) & 0x01) == 1) {
		if (otherKeyTable[0][1]) {
			playbackDisp();
			playbackOpt();
			memset(otherKeyTable[0],0,sizeof(otherKeyTable[0]));
			otherKeyTable[0][1] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 16) & 0x01) == 1) {
		if(otherKeyTable[0][2]) {
			deleteDisp();
			deleteOpt();
			memset(otherKeyTable[0],0,sizeof(otherKeyTable[0]));
			otherKeyTable[0][2] = 1;
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
 * Row 2 of the keypad corresponds to waveform selection
 */
void checkRow2(void) {

	setRow2();
	wait_us(250);

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		if (otherKeyTable[1][0] == 0) {
			squareWaveDisp();
			squareWave();
			memset(otherKeyTable[1],0,sizeof(otherKeyTable[1]));
			otherKeyTable[1][0] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 15) & 0x01) == 1) {
		if (otherKeyTable[1][1] == 0) {
			triangleWaveDisp();
			triangleWave();
			memset(otherKeyTable[1],0,sizeof(otherKeyTable[1]));
			otherKeyTable[1][1] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 16) & 0x01) == 1) {
		if (otherKeyTable[1][2] == 0) {
			sineWaveDisp();
			sineWave();
			memset(otherKeyTable[1],0,sizeof(otherKeyTable[1]));
			otherKeyTable[1][2] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf("You have pressed B.\n");
		wait_us(50000);
	}

	wait_us(50000);
	rowReset();
	wait_us(250);

}

/*
 * Row 3 of the keypad corresponds to click track speed selection
 */
void checkRow3(void) {

	setRow3();
	wait_us(250);

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
			if (otherKeyTable[2][0] ==0) {
			slowClickDisp();
			slowClick();
			memset(otherKeyTable[2],0,sizeof(otherKeyTable[2]));
			otherKeyTable[2][0] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 15) & 0x01) == 1) {
		if (otherKeyTable[2][1] ==0) {
			normalClickDisp();
			normalClick();
			memset(otherKeyTable[2],0,sizeof(otherKeyTable[2]));
			otherKeyTable[2][1] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 16) & 0x01) == 1) {
		if (otherKeyTable[2][2] ==0) {
			fastClickDisp();
			fastClick();
			memset(otherKeyTable[2],0,sizeof(otherKeyTable[2]));
			otherKeyTable[2][2] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf("You have pressed C.\n");
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

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		if (otherKeyTable[3][0] ==0) {
			resetDisp();
			resetOpt();
			memset(otherKeyTable[3],0,sizeof(otherKeyTable[3]));

			// We don't want this key press to be remembered!
			// otherKeyTable[3][0] = 1;
		}
		wait_us(50000);
	}
	else if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf("You have pressed 0.\n");
		wait_us(50000);
	}
	else if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf("You have pressed #.\n");
		wait_us(50000);
	}
	else if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf("You have pressed D.\n");
		wait_us(50000);
	}

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
