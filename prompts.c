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
	char options[] = "Use the keypad to select option";
	displayWords(options,(sizeof(options)-1));
	wait_us(250);
}

/*
 * "7) Play notes and record 8) Play chords"
 */
void initialPrompt(void) {
	char options[] = "7) Play notes and record 8) Play chords ";
	displayWords(options,(sizeof(options)-1));
	wait_us(250);
}

/*
 * "1) Playback 2) Save 3) Edit *) Reset"
 */
void postRecPrompt(void) {
	char options[] = "1) Playback 2) Save 3) Edit *) Reset";
	displayWords(options,(sizeof(options)-1));
	wait_us(250);
}

/*
 * "You have selected the record option."
 */
void recordDisp(void) {
	char record[] = "You have selected to record.";
	displayWords(record,(sizeof(record)-1));
	wait_us(250);
}

/*
 * "Use the keyboard to record your song."
 */
void recordPrompt(void) {
	char record[] = "Use the keyboard to record your song.";
	displayWords(record,(sizeof(record)-1));
	wait_us(250);
}

/*
 * "Playing chords. Press * to exit."
 */
void chordDisp(void) {
	char chord[] = "Playing chords. Press * to exit.";
	displayWords(chord,(sizeof(chord)-1));
	wait_us(250);
}
/*
 * "Saving song to memory."
 */
void saveToMemDisp(void) {
	char save[] = "Saving song to memory.";
	displayWords(save,(sizeof(save)-1));
	wait_us(250);
}

/*
 * "Press 0 to access your song from memory."
 */
void playFromMemDisp(void) {
	char play[] = "Press 0 to access your song from memory.";
	displayWords(play,(sizeof(play)-1));
	wait_us(250);
}
/*
 * "Accessing song from memory."
 */
void accessingDisp(void) {
	char save[] = "Accessing song from memory.";
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
 * "What a lovely song."
 */
void lovelySong(void) {
	char lovely[] = "What a lovely song.";
	displayWords(lovely,(sizeof(lovely)-1));
	wait_us(250);
}

/*
 * "You have selected to edit your song."
 */
void editDisp(void) {
	char edit[] = "You have selected to edit your song.";
	displayWords(edit,(sizeof(edit)-1));
	wait_us(250);
}

/*
 * "Use the keyboard to edit your song."
 */
void editPrompt(void) {
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
void clickDisp(void) {
	char click[] = "Please select the click speed";
	displayWords(click,(sizeof(click)-1));
	wait_us(250);
}

/*
 * "4) Slow 5) Normal 6) Fast B) None"
 */
void clickPrompt(void) {
	char click[] = "4) Slow 5) Normal 6) Fast B) None";
	displayWords(click,(sizeof(click)-1));
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
