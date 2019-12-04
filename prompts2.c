#include "final.h"

/*
 * "Welcome to the music editor!"
 */
void welcomeDisp(void) {
	char welcome[] = "Welcome to our game!";
	displayWords2(welcome,(sizeof(welcome)-1));
	wait_us(250);
}

/*
 * "Select from the following options using the keypad:"
 */
void editor1Prompt(void) {
	char options1[] = "Use keypad to select option:";
	displayWords2(options1,(sizeof(options1)-1));
	wait_us(250);
}

/*
 * "1) Record
 *  2) Playback
 *  3) Delete
 *  *) Reset"
 */
void editor2Prompt(void) {
	char options2[] = "2) Playback 3) Edit *) Reset";
	displayWords2(options2,(sizeof(options2)-1));
	wait_us(250);
}

/*
 * "You have selected the record option."
 */
void record1Disp(void) {
	char record[] = "You have entered recording mode.";
	displayWords2(record,(sizeof(record)-1));
	wait_us(250);
}

void record2Disp(void) {
	char record[] = "Use the keyboard to record your song.";
	displayWords2(record,(sizeof(record)-1));
	wait_us(250);
}

/*
 * "You chose to listen to your song."
 */
void playback1Disp(void) {
	char playback[] = "You chose to listen to your song.";
	displayWords2(playback,(sizeof(playback)-1));
	wait_us(250);
}

/*
 * "Playing current track."
 */
void playback2Disp(void) {
	char playback[] = "You chose to listen to your song.";
	displayWords2(playback,(sizeof(playback)-1));
	wait_us(250);
}

/*
 * "You have selected to delete current song."
 */
void deleteDisp(void) {
	char delete[] = "You have selected to delete current song.";
	displayWords2(delete,(sizeof(delete)-1));
	wait_us(250);
}

/*
 * "You chose to reset. Press * to continue."
 */
void resetDisp(void) {
	char reset[] = "You chose to reset. Press * to continue.";
	displayWords2(reset,(sizeof(reset)-1));
	wait_us(250);
}
/*
 * "Use keypad to select waveform."
 */
void wave1Prompt(void) {
	char waveform1[] = "Use keypad to select waveform.";
	displayWords2(waveform1,(sizeof(waveform1)-1));
	wait_us(250);
}

/*
 * "4) Square 5) Triangle 6) Sine *) Reset"
 */
void wave2Prompt(void) {
	char waveform2[] = "4) Square 5) Triangle 6) Sine *) Reset";
	displayWords2(waveform2,(sizeof(waveform2)-1));
	wait_us(250);
}

/*
 * "You have selected square waveform."
 */
void squareWaveDisp(void) {
	char square[] = "You have selected square waveform.";
	displayWords2(square,(sizeof(square)-1));
	wait_us(250);
}

/*
 * "You have selected triangle waveform."
 */
void triangleWaveDisp(void) {
	char triangle[] = "You have selected triangle waveform.";
	displayWords2(triangle,(sizeof(triangle)-1));
	wait_us(250);
}

/*
 * "You have selected sine waveform."
 */
void sineWaveDisp(void) {
	char sine[] = "You have selected sine waveform.";
	displayWords2(sine,(sizeof(sine)-1));
	wait_us(250);
}

/*
 * "Use keypad to select click speed."
 */
void click1Prompt(void) {
	char click1[] = "Use keypad to select click speed.";
	displayWords2(click1,(sizeof(click1)-1));
	wait_us(250);
}

/*
 * "7) Slow 8) Normal 9) Fast OR C) None"
 */
void click2Prompt(void) {
	char click2[] = "7) Slow 8) Normal 9) Fast C) None";
	displayWords2(click2,(sizeof(click2)-1));
	wait_us(250);
}
/*
 * "You have selected slow click."
 */
void slowClickDisp(void) {
	char slowClick[] = "You have selected slow click.";
	displayWords2(slowClick,(sizeof(slowClick)-1));
	wait_us(250);
}

/*
 * "You have selected normal click."
 */
void normalClickDisp(void) {
	char normalClick[] = "You have selected normal click.";
	displayWords2(normalClick,(sizeof(normalClick)-1));
	wait_us(250);
}

/*
 * "You have selected fast click."
 */
void fastClickDisp(void) {
	char fastClick[] = "You have selected fast click.";
	displayWords2(fastClick,(sizeof(fastClick)-1));
	wait_us(250);
}

/*
 * "You have selected no click."
 */
void noClickDisp(void) {
	char noClick[] = "You have selected no click.";
	displayWords2(noClick,(sizeof(noClick)-1));
	wait_us(250);
}
