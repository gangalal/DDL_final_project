#include "final.h"

/*
 * Potential fix for click track??
 */
extern void clickTrack(void) {
	if (keypad[2][0] == 1) {
		configT3MR0(5);
	}
	else if (keypad[2][1] == 1) {
		configT3MR0(11);
	}
	else if (keypad[2][2] == 1) {
		configT3MR0(21);
	}
	else {
		timer3Stop();
	}
}
