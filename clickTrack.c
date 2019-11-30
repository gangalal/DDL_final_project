#include "final.h"

/*
 * Generate a slow click track
 */
void slowClick(void) {
	configT3MR0(1);
}

/*
 * Generate a normal click track
 */
void normalClick(void) {
	configT3MR0(2);
}

/*
 * Generate a fast click track
 */
void fastClick(void) {
	configT3MR0(3);
}
