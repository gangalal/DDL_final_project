/*
===============================================================================
 Name        : eeprom.h
 Author      : Daniel Glover
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

#include "i2c.h"

/*
 * Write to the EEPROM
 */
void memWrite(int data) {
    int addr = 0b1010000; // EEprom address
    I2CStart();
	I2CWrite(addr << 1); // last bit 0 for write
	I2CWrite(32); // address to write to
	for (int i = 0; i<25; i++){ // index array values
		I2CWrite(data[i]); // write in array index value
	}
	I2CStop();
	wait_us(100);
}

/*
 * Read from the EEPROM
 */
void memRead(int data) {
	int addr = 0b1010000; // EEprom address
	int count = 0;
	I2CStart();
	I2CWrite(addr << 1); // last bit 0 for write
	I2CWrite(32);
	I2CStart();
	I2CWrite((addr << 1) + 1); // last bit shifted to 1 for read
	for (int i = 0; i<25;i++) {
		if (i<24) {
			int tester = I2CRead(1);
			if (tester == data[i]){
				count++;
		  } else {
			int tester = I2CRead(0);
				if (tester == data[i]) {
				count++;
				}
			}

			}
		}
	I2CStop();
	wait_us(100);
	if (count == 25) { // if the counter sees the correct 25 notes
		// insert printf command or LCD screen shot
	}
}
