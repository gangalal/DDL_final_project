#ifndef FINAL_H_
#define FINAL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "registerDef.h"

/*
 * EEPROM functions
 */
extern int storedData1[8];
extern int storedData2[8];
extern int storedData3[8];
extern int storedData4[8];
extern void memWrite(int* data);
extern void memRead(int* data);
extern void populateData(void);

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
extern char keypad[4][4];
extern void keypadInit(void);
void resetRow1Sel(void);
void resetRow2Sel(void);
void resetRow3Sel(void);
void resetAllSel(void);
extern void rowReset(void);
extern void setRow1(void);
extern void setRow2(void);
extern void setRow3(void);
extern void setRow4(void);
extern void checkRow1(void);
extern void checkRow2(void);
extern void checkRow3(void);
extern void checkRow4(void);

/*
 * LCD functions
 */
extern void lcdInit(void);
extern void LCDCmd(int data);
//extern void LCDinitCmd(void);
extern void LCDinitChar(void);
extern void displayChar(int data);
extern void displayWords(char* array, int arraySize);

/*
 * MIDI struct and functions
 */
extern int receivedData[25];
extern int noteLength[25];
extern void configMIDI(void);
extern void recordSquareWF(int* byte);

/*
 * Functions for selected options
 */
extern int data[8];
extern int count;
extern void recordOpt(void);
extern void playbackOpt(void);
extern void playChordsOpt(void);
extern void saveToMemOpt(void);
extern void playFromMem(int* storedData);
extern void playFromMemOpt(void);
extern void editOpt(void);
extern void resetOpt(void);

/*
 * Display and prompt functions
 */
extern void welcomeDisp(void);
extern void editorDisp(void);
extern void initialPrompt(void);
extern void postRecPrompt(void);
extern void recordDisp(void);
extern void recordPrompt(void);
extern void chordDisp(void);
extern void saveToMemDisp(void);
extern void playFromMemDisp(void);
extern void accessingDisp(void);
extern void saveDisp(void);
extern void playbackDisp(void);
extern void lovelySong(void);
extern void editDisp(void);
extern void editPrompt(void);
extern void resetDisp(void);
extern void clickDisp(void);
extern void clickPrompt(void);
extern void slowClickDisp(void);
extern void normalClickDisp(void);
extern void fastClickDisp(void);
extern void noClickDisp(void);

/*
 * Timer Functions for Timers 0, 1, 2, and 3
 */
extern void timer0Init();
extern void timer0Start();
extern void timer0Stop();
extern void timer0Reset();
extern int timer0Read_us();
extern void wait_us(int usec);

extern void timer1Init();
extern void timer1Start();
extern void timer1Stop();
extern void timer1Reset();
extern int timer1Read_us();
extern void wait1_us(int usec);

extern void timer2Init();
extern void timer2Stop();
extern void configT2MR2(int freq);
extern void configT2MR3(int freq);

extern void timer3Init();
extern void timer3Stop();
extern void configT3MR0(int freq);

#endif /* FINAL_H_ */
