#include "final.h"

/*
 * "Welcome to our game!"
 */
void welcomeDisp(void) {
	char welcome[] = "Welcome to our game!";
	displayWords2(welcome,(sizeof(welcome)-1));
	wait_us(250);
}

/*
 * "Select from the following options using the keypad:"
 */
void options1Prompt(void) {
	char options1[] = "Select from the following options using the keypad:";
	displayWords2(options1,(sizeof(options1)-1));
	wait_us(250);
}

/*
 * "1) Record
 *  2) Playback
 *  3) Delete
 *  *) Reset"
 */
void options2Prompt(void) {
	char options2[] = "1) Record \n 2) Playback \n 3) Delete \n *) Reset";
	displayWords2(options2,(sizeof(options2)-1));
	wait_us(250);
}

/*
 * "You have selected the record option."
 */
void recordDisp(void) {
	char record[] = "You have selected the record option.";
	displayWords2(record,(sizeof(record)-1));
	wait_us(250);
}

/*
 * "You have selected the playback option."
 */
void playbackDisp(void) {
	char playback[] = "You have selected the playback option.";
	displayWords2(playback,(sizeof(playback)-1));
	wait_us(250);
}

/*
 * "You have selected the delete option."
 */
void deleteDisp(void) {
	char delete[] = "You have selected the delete option.";
	displayWords2(delete,(sizeof(delete)-1));
	wait_us(250);
}

/*
 * "You have selected the reset option. Press * to continue."
 */
void resetDisp(void) {
	char reset[] = "You have selected the reset option. Press * to continue.";
	displayWords2(reset,(sizeof(reset)-1));
	wait_us(250);
}
/*
 * "Please select from the following waveform options using the keypad:"
 */
void waveform1Prompt(void) {
	char waveform1[] = "Please select from the following waveform options using the keypad:";
	displayWords2(waveform1,(sizeof(waveform1)-1));
	wait_us(250);
}

/*
 * "4) Square Waveform
 *  5) Triangle Waveform
 *  6) Sine Waveform
 *  *) Reset
 */
void waveform2Prompt(void) {
	char waveform2[] = "4) Square Waveform \n 5) Triangle Waveform \n 6) Sine Waveform \n *) Reset";
	displayWords2(waveform2,(sizeof(waveform2)-1));
	wait_us(250);
}

/*
 * "You have selected the square waveform."
 */
void squareWaveDisp(void) {
	char square[] = "You have selected the square waveform.";
	displayWords2(square,(sizeof(square)-1));
	wait_us(250);
}

/*
 * "You have selected the triangle waveform."
 */
void triangleWaveDisp(void) {
	char triangle[] = "You have selected the triangle waveform.";
	displayWords2(triangle,(sizeof(triangle)-1));
	wait_us(250);
}

/*
 * "You have selected the sine waveform."
 */
void sineWaveDisp(void) {
	char sine[] = "You have selected the sine waveform.";
	displayWords2(sine,(sizeof(sine)-1));
	wait_us(250);
}

/*
 * "You have selected the slow click track speed."
 */
void slowClickDisp(void) {
	char slowClick[] = "You have selected the slow click track speed.";
	displayWords2(slowClick,(sizeof(slowClick)-1));
	wait_us(250);
}

/*
 * "You have selected the normal click track speed."
 */
void normalClickDisp(void) {
	char normalClick[] = "You have selected the normal click track speed.";
	displayWords2(normalClick,(sizeof(normalClick)-1));
	wait_us(250);
}

/*
 * "You have selected the fast click track speed."
 */
void fastClickDisp(void) {
	char fastClick[] = "You have selected the fast click track speed.";
	displayWords2(fastClick,(sizeof(fastClick)-1));
	wait_us(250);
}
