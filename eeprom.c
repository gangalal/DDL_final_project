#include "final.h"

int storedData1[8];
int storedData2[8];
int storedData3[8];
int storedData4[8];

/*
 * Write to the EEPROM
 */
void memWrite(int* data) {

	int addr = 0b1010000; // EEprom address
	I2CStart();
	I2CWrite(addr << 1); // last bit 0 for write
	I2CWrite(32); // address to write to
	for (int i = 0; i < 8; i++) { // index array values
		I2CWrite(data[i]); // write in array index value
	}
	I2CStop();
	wait_us(5000000);

}

/*
 * Read from the EEPROM
 */
void memRead(int* data) {

	int memData[8];
	int addr = 0b1010000; // EEprom address
	int count = 0;
	I2CStart();
	I2CWrite(addr << 1); // last bit 0 for write
	I2CWrite(32);
	I2CStart();
	I2CWrite((addr << 1) + 1); // last bit shifted to 1 for read
	for (int i = 0; i < 8; i++) {
		if (i < 8) {
			int tester = I2CRead(1);
			if (tester == data[i]) {
				count++;
				memData[i] = tester;
			} else {
				int tester = I2CRead(0);
				if (tester == data[i]) {
					count++;
					memData[i] = tester;
				}
			}

		}
	}
	I2CStop();
	wait_us(1000);

	for (int i = 0; i < 8; i++)
		printf("stored data %x\n", memData[i]);

//	for (int i = 0; i < 8; i++) {
//		if (memData[i] == 0x3c) {
//			configT2MR3(259);		// play middle c (C4)
//			wait1_us(noteLength[i]);
//			configT2MR3(0);
//		} else if (memData[i] == 0x3e) {
//			configT2MR3(291);		// play D4
//			wait1_us(noteLength[i]);
//			configT2MR3(0);
//		} else if (memData[i] == 0x40) {
//			configT2MR3(327);		// play E4
//			wait1_us(noteLength[i]);
//			configT2MR3(0);
//		} else if (memData[i] == 0x41) {
//			configT2MR3(347);		// play F4
//			wait1_us(noteLength[i]);
//			configT2MR3(0);
//		} else if (memData[i] == 0x43) {
//			configT2MR3(389);		// play G4
//			wait1_us(noteLength[i]);
//			configT2MR3(0);
//		} else if (memData[i] == 0x45) {
//			configT2MR3(437);		// play A4
//			wait1_us(noteLength[i]);
//			configT2MR3(0);
//		} else if (memData[i] == 0x47) {
//			configT2MR3(490);		// play B4
//			wait1_us(noteLength[i]);
//			configT2MR3(0);
//		} else if (memData[i] == 0x48) {
//			configT2MR3(519);		// play C5 (full octave)
//			wait1_us(noteLength[i]);
//			configT2MR3(0);
//		}
//		wait_us(10000);
//	}

}

/*
 * Play a stored song
 */
void populateData(void) {

	int temp = 0;

	// store bytes 0-7 with note values
	for (int i = 0; i < 8; i++) {
		storedData1[i] = receivedData[temp];
		temp++;
	}

	// store bytes 8-15 with note values
	for (int i = 0; i < 8; i++) {
		storedData2[i] = receivedData[temp];
		temp++;
	}

	// store bytes 16-23 with note values
	for (int i = 0; i < 8; i++) {
		storedData3[i] = receivedData[temp];
		temp++;
	}

	// store byte 24 with note values
	for (int i = 0; i < 1; i++) {
		storedData4[i] = receivedData[temp];
		temp++;
	}

}
