/*
 * final.h
 *
 *  Created on: Nov 30, 2019
 *      Author: Jess_
 */

#ifndef FINAL_H_
#define FINAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "registerDef.h"

/*
 * Generate click tracks
 */
extern void slowClick(void);
extern void normalClick(void);
extern void fastClick(void);

/*
 * EEPROM functions
 */
extern void memWrite(int* data);
extern void memRead(int* data);

/*
 * I2C functions
 */
extern void I2CInit();
extern void I2CStart();
extern void I2CWrite(int data);
extern int I2CRead(int ack);
extern void I2CStop();

/*
 * Keypad functions
 */
extern void keypadInit(void);
extern void rowReset();
extern void setRow1(void);
extern void setRow2(void);
extern void setRow3(void);
extern void setRow4(void);
extern void checkRow1(void);
extern void checkRow2(void);
extern void checkRow3(void);
extern void checkRow4(void);
extern void keyScan(void);

/*
 * LCD functions
 */
extern void lcdInit(void);
extern void LCDCmd(int data);
extern void LCDinitCmd(void);
extern void LCDchar(int data);
extern void LCDinitChar(void);
extern void displayChar(int data);
extern void displayWords(int* array, int arraySize);
extern void displayWords2(char* array, int arraySize);

/*
 * MIDI struct and functions
 */
struct _MIDIData {
	int key;
	int order;
	int flag;
};
typedef struct _MIDIData MIDIData; //defining struct type
extern MIDIData receivedData[8];
extern void configMIDI(void);
extern void playMIDIByte(int byte);
extern void readMIDIByte(int byte1, int byte2);
extern void check(int* byte);

/*
 * Functions for selected options
 */
extern void recordOpt(void);
extern void playbackOpt(void);
extern void deleteOpt(void);
extern void resetOpt(void);

/*
 * Display and prompt functions
 */
extern void welcomeDisp(void);
extern void options1Prompt(void);
extern void options2Prompt(void);
extern void recordDisp(void);
extern void playbackDisp(void);
extern void deleteDisp(void);
extern void resetDisp(void);
extern void waveform1Prompt(void);
extern void waveform2Prompt(void);
extern void squareWaveDisp(void);
extern void triangleWaveDisp(void);
extern void sineWaveDisp(void);
extern void slowClickDisp(void);
extern void normalClickDisp(void);
extern void fastClickDisp(void);

/*
 * Timer Functions for Timers 0, 2, and 3
 */
extern void timer0Init();
extern void timer0Start();
extern void timer0Stop();
extern void timer0Reset();
extern int timer0Read_us();
extern void wait_us(int usec);
extern void wait_ticks(unsigned long count);
extern void waitOneSecond(unsigned long count);

extern void timer2Init();
extern void configT2MR3(int freq);
extern void timer2genFreq(int freq);

extern void timer3Init();
extern void configT3MR0(int freq);
extern void timer3genFreq(int freq);

/*
 * Waveform functions
 */
extern void squareWave(void);
extern void triangleWave(void);
extern void sineWave(void);

#endif /* FINAL_H_ */
