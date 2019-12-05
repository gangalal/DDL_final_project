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
extern char keypad[4][4];
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
extern void displayWords(char* array, int arraySize);

/*
 * MIDI struct and functions
 */

//typedef struct _MIDIData MIDIData; //defining struct type
extern int count;
extern int receivedData[25];
extern int noteLength[25];
extern void configMIDI(void);
extern void recordSquareWF(int* byte);
extern void playMIDIChord(int*byte);

/*
 * Functions for selected options
 */
extern int data[8];
extern void recordOpt(void);
extern void playbackOpt(void);
extern void playChordsOpt(void);
extern void saveOpt(void);
extern void editOpt(void);
extern void resetOpt(void);
extern void initialRoutine(void);
extern void preRecordingRoutine(void);
extern void postRecordingRoutine(void);

/*
 * Display and prompt functions
 */
extern void welcomeDisp(void);
extern void editorDisp(void);
extern void initialPrompt(void);
extern void postRecPrompt(void);
extern void record1Disp(void);
extern void record2Disp(void);
extern void chordExitDisp(void);
extern void saveDisp(void);
extern void playbackDisp(void);
extern void editDisp(void);
extern void edit2Disp(void);
extern void resetDisp(void);
extern void click1Disp(void);
extern void click1Prompt(void);
extern void slowClickDisp(void);
extern void normalClickDisp(void);
extern void fastClickDisp(void);
extern void noClickDisp(void);

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

extern void timer1Init();
extern void timer1Start();
extern void timer1Stop();
extern void timer1Reset();
extern int timer1Read_us();
extern void wait1_us(int usec);

extern void timer2Init();
extern void configT2MR2(int freq);
extern void configT2MR3(int freq);

extern void timer3Stop();
extern void timer3Init();
extern void configT3MR0(int freq);

extern int waveTable[256];
extern void fillWaveTable(void);
extern void triangleWave(int count, int step);
extern void sineWave(int freq);

#endif /* FINAL_H_ */
