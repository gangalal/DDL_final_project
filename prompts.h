#ifndef PROMPTS_H_
#define PROMPTS_H_

#include "lcd.h"

/*
 * "Welcome to our game!"
 */
void welcomePrompt(void) {
	int welcome[20] = {0x57, 0x65, 0x6C, 0x63, 0x6F, 0x6D, 0x65, 0x20, 0x74,
			0x6F, 0x20, 0x6F, 0x75, 0x72, 0x20, 0x67, 0x61, 0x6D, 0x65, 0x21};
	int welcomeLen = sizeof(welcome);
	displayWords(welcome, welcomeLen);
	waitOneSecond(1);
}

/*
 * "Select from the following options using the keypad:"
 */
void options1Prompt(void) {
	int options1[51] = {0x53, 0x65, 0x6C, 0x65, 0x63, 0x74, 0x20, 0x66, 0x72,
			0x6F, 0x6D, 0x20, 0x74, 0x68, 0x65, 0x20, 0x66, 0x6F, 0x6C, 0x6C,
			0x6F, 0x77, 0x69, 0x6E, 0x67, 0x20, 0x6F, 0x70, 0x74, 0x69, 0x6F,
			0x6E, 0x73, 0x20, 0x75, 0x73, 0x69, 0x6E, 0x67, 0x20, 0x74, 0x68,
			0x65, 0x20, 0x6B, 0x65, 0x79, 0x70, 0x61, 0x64, 0x3A};
	int options1Len = sizeof(options1);
	displayWords(options1,options1Len);
	waitOneSecond(1);
}
/*
 * "1) Record
 *  2) Playback
 *  3) Delete
 *  *) Reset"
 */
void options2Prompt(void) {
	int options2[37] = {0x31, 0x29, 0x20, 0x52, 0x65, 0x63, 0x6F, 0x72, 0x64,
			0x0A, 0x32, 0x29, 0x20, 0x50, 0x6C, 0x61, 0x79, 0x62, 0x61, 0x63,
			0x6B, 0x0A, 0x33, 0x29, 0x20, 0x44, 0x65, 0x6C, 0x74, 0x65, 0x0A,
			0x33, 0x29, 0x20, 0x52, 0x65, 0x73, 0x65, 0X74};
	int options2Len = sizeof(options2);
	displayWords(options2,options2Len);
	waitOneSecond(1);
}

void deletePrompt(void) {

}



#endif /* PROMPTS_H_ */
