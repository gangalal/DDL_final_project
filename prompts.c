#include "final.h"

/*
 * "Welcome to Music Editor!"
 */
void welcomeDisp(void) {
	char welcome[] = "Welcome to Music Editor!";
	displayWords(welcome,(sizeof(welcome)-1));
	wait_us(250);
}

/*
 * "Use the keypad to select option."
 */
void editorDisp(void) {
	char options1[] = "Use the keypad to select option";
	displayWords(options1,(sizeof(options1)-1));
	wait_us(250);
}

/*
 * "7) Play notes and record 8) Play chords freely"
 */
void initialPrompt(void) {
	char options1[] = "7) Play notes and record 8) Play chords ";
	displayWords(options1,(sizeof(options1)-1));
	wait_us(250);
}

/*
 * "1) Playback 2) Save 3) Edit *) Reset"
 */
void postRecPrompt(void) {
	char options2[] = "1) Playback 2) Save 3) Edit *) Reset";
	displayWords(options2,(sizeof(options2)-1));
	wait_us(250);
}

/*
 * "You have selected the record option."
 */
void record1Disp(void) {
	char record[] = "You have selected to record.";
	displayWords(record,(sizeof(record)-1));
	wait_us(250);
}

/*
 * "Use the keyboard to record your song."
 */
void record2Disp(void) {
	char record[] = "Use the keyboard to record your song.";
	displayWords(record,(sizeof(record)-1));
	wait_us(250);
}

/*
 * "Playing chords. Press * to exit."
 */
void chordExitDisp(void) {
	char chord[] = "Playing chords. Press * to exit.";
	displayWords(chord,(sizeof(chord)-1));
	wait_us(250);
}
/*
 * "You have selected to save your song."
 */
void saveDisp(void) {
	char save[] = "You have selected to save your song.";
	displayWords(save,(sizeof(save)-1));
	wait_us(250);
}
/*
 * "You have selected to listen to your song."
 */
void playbackDisp(void) {
	char playback[] = "You have selected to listen to your song.";
	displayWords(playback,(sizeof(playback)-1));
	wait_us(250);
}

/*
 * "You have selected to edit your song."
 */
void editDisp(void) {
	char delete[] = "You have selected to edit your song.";
	displayWords(delete,(sizeof(delete)-1));
	wait_us(250);
}

/*
 * "Use the keyboard to edit your song."
 */
void edit2Disp(void) {
	char record[] = "Use the keyboard to edit your song.";
	displayWords(record,(sizeof(record)-1));
	wait_us(250);
}

/*
 * "Reset selected."
 */
void resetDisp(void) {
	char reset[] = "Reset selected.";
	displayWords(reset,(sizeof(reset)-1));
	wait_us(250);
}

/*
 * "Please select the click speed using the keypad"
 */
void click1Disp(void) {
	char click1[] = "Please select the click speed";
	displayWords(click1,(sizeof(click1)-1));
	wait_us(250);
}

/*
 * "4) Slow 5) Normal 6) Fast B) None"
 */
void click1Prompt(void) {
	char click2[] = "4) Slow 5) Normal 6) Fast B) None";
	displayWords(click2,(sizeof(click2)-1));
	wait_us(250);
}
/*
 * "You have selected slow click."
 */
void slowClickDisp(void) {
	char slowClick[] = "You have selected slow click.";
	displayWords(slowClick,(sizeof(slowClick)-1));
	wait_us(250);
}

/*
 * "You have selected normal click."
 */
void normalClickDisp(void) {
	char normalClick[] = "You have selected normal click.";
	displayWords(normalClick,(sizeof(normalClick)-1));
	wait_us(250);
}

/*
 * "You have selected fast click."
 */
void fastClickDisp(void) {
	char fastClick[] = "You have selected fast click.";
	displayWords(fastClick,(sizeof(fastClick)-1));
	wait_us(250);
}

/*
 * "You have selected no click."
 */
void noClickDisp(void) {
	char noClick[] = "You have selected no click.";
	displayWords(noClick,(sizeof(noClick)-1));
	wait_us(250);
}
