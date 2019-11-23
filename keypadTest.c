/*
===============================================================================
 Name        : keypadTest.c
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

#define FIO0DIR (*(volatile unsigned int *)0x2009c000)
#define FIO0PIN (*(volatile unsigned int *)0x2009c014)
#define FIO0SET (*(volatile unsigned int *)0x2009C018)
#define FIO0CLR (*(volatile unsigned int *)0x2009C01C)

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
 * Initialize pins as inputs and outputs, initialize pull-up/pull-down resistors
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

}

/*
 * Determine if a key in Row 1 has been pressed and prints test statement
 */
void checkKeyRow1(void) {
	
	/*
	 * Set Row 1 high, the rest low
	 */
	FIO0PIN |= (1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf('You have pressed 1.');
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf('You have pressed 2.');
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf('You have pressed 3.');
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf('You have pressed A.');
	}

	/*
	 * Set Row 1 low
	 */
	FIO0PIN &= ~(1 << 6);

}

/*
 * Determine if a key in Row 2 has been pressed and prints test statement
 */
void checkKeyRow2(void) {
	
	/*
	 * Set Row 2 high, the rest low
	 */
	FIO00PIN |= (1 << 0);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 1);
	FIO0PIN &= ~(1 << 18);

	/*
	 * Scan each Column input for high value
	 */
	if (((FIO0PIN >> 17) & 0x01) == 1) {
		printf('You have pressed 4.');
	}
	if (((FIO0PIN >> 15) & 0x01) == 1) {
		printf('You have pressed 5.');
	}
	if (((FIO0PIN >> 16) & 0x01) == 1) {
		printf('You have pressed 6.');
	}
	if (((FIO0PIN >> 23) & 0x01) == 1) {
		printf('You have pressed B.');
	}

	/*
	 * Set Row 2 low
	 */
	FIO0PIN &= ~(1 << 0);

}

/*
 * Determine if a key in Row 3 has been pressed and prints test statement
 */
void checkKeyRow3(void) {
	
	/*
	 * Set Row 3 high, the rest low
	 */
	FIO0PIN |= (1 << 1);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 18);
	
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

	/*
	 * Set Row 3 low
	 */
	FIO0PIN |= (1 << 1);

}

/*
 * Determine if a key in Row 4 has been pressed and prints test statement
 */
void checkKeyRow4(void) {
	
	/*
	 * Set Row 4 high, the rest low
	 */
	FIO0PIN |= (1 << 18);
	FIO0PIN &= ~(1 << 6);
	FIO0PIN &= ~(1 << 0);
	FIO0PIN &= ~(1 << 1);
	
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

	/*
	 * Set Row 4 low
	 */
	FIO0PIN &= ~(1 << 18);

}

/*
 * Scan for pressed key
 */
void keyScan() {

	checkKeyRow1();
	checkKeyRow2();
	checkKeyRow3();
	checkKeyRow4();

}
/*
 * Scans keypad for pressed key and returns test statement when a key has been pressed
 */
int main(void) {

	initIO();

	while(1) {
		
		keyScan();
        
    }
    return 0 ;
}
