/*
===============================================================================
 Name        : keypad.h
 Author      : Jessica Horner
 Version     : Alpha
 Copyright   : $(copyright)
 Description : ** Needs description still **
===============================================================================
*/

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>

#include <timer.h>

#define PINMODE0 (*(volatile unsigned int *)0x4002c040)
#define PINMODE1 (*(volatile unsigned int *)0x4002c044)
#define FIO0DIR (*(volatile unsigned int *)0x2009c000)
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)

/*
 * If we use this method - we must manually refer to the key
 * keyTable[row*4 + column]
 */
char keyTable[] = 	"1 2 3 A"
			"4 5 6 B"
			"7 8 9 C"
			"* 0 # D";

/*
 * If we use this method - we have to be CAREFUL with syntax!
 * keyTable[row][col]
 *
 * Jessica prefers this method - can see EXACTLY what you need right away
 */
char otherKeyTable[] = {{'1','2','3','A'},
			{'4','5','6','B'},
			{'7','8','9','C'},
			{'*','0','#','D'}};

/*
 * Initialize GPIO0 pins as inputs and outputs, 
 * Initialize pull-up/pull-down resistors
 */
void initIO(void) {

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


}

/*
 * Set pins 8-11 low
 */
void rowReset() {

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

	FIO00PIN |= (1 << 0);
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

	/*
	 * Row 1 of the keypad corresponds to waveform selection
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf('You have selected the square waveform.');
		// TODO input command for square waveform & LCD display info
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf('You have selected the triangle waveform.');
		// TODO input command for triangle waveform & LCD display info
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf('You have selected the sine waveform.');
		// TODO input command for sine waveform & LCD display info
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf('You have pressed A.');
	}

	rowReset();

}

/*
 * Row 2 of the keypad corresponds to click track speed
 */
void checkRow2(void) {

	setRow2();

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf('You have selected the slow click track speed.');
		// TODO input command for slow click track speed & LCD display info
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf('You have selected the normal click track speed.');
		// TODO input command for normal click track speed & LCD display info
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf('You have selected the high click track speed.');
		// TODO input command for high click track speed & LCD display info
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf('You have pressed B.');
	}

	rowReset();

}

/*
 * Determine if a key in Row 3 has been pressed and prints test statement
 */
void checkRow3(void) {

	setRow3();

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf('You have pressed 7.');
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf('You have pressed 8.');
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf('You have pressed 9.');
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf('You have pressed C.');
	}

	rowReset();
}

/*
 * Determine if a key in Row 4 has been pressed and prints test statement
 */
void checkRow4(void) {

	setRow4();

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf('You have pressed *.');
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf('You have pressed 0.');
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf('You have pressed #.');
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf('You have pressed D.');
	}

	rowReset();

}

/*
 * Scan for pressed key
 * We can combine the checkRow functions if we want to - kept it separate until
 * we determine which rows we will be using. This will depend on how many
 * functions we end up needing to use on the keypad.
 */
void keyScan() {

	checkRow1();
	checkRow2();
	checkRow3();
	checkRow4();

}
