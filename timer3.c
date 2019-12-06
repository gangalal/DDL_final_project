#include "final.h"
/**
 * Start Timer 3
 */
static inline void timer3Start() {

	T3TCR |= (1 << 0);

}

/**
 * Stop Timer 3
 */
void timer3Stop() {

	T3TCR &= ~(1 << 0);

}
/**
 * Reset Timer 3
 */
static inline void timer3Reset() {

	T3TCR |= (1 << 1);
	while (T3TC != 0) {
		// wait until timer has changed
	}
	T3TCR &= ~(1 << 1);

}

/**
 * Initialize Timer 3 to control the timing of decay for each tone
 */
void timer3Init() {

	PCONP |= (1 << 23);		// Timer 3 Enable
	PCLKSEL1 &= ~(1 << 14); // Reset clock selection on Timer 3, default = 1MHz
	PCLKSEL1 &= ~(1 << 15); // Reset clock selection on Timer 3, default = 1MHz
	PINSEL0 |= (1 << 20);	// Select Timer 3, Match register 0 on LPC P0.9
	PINSEL0 |= (1 << 21); // Select Timer 3, Match register 0 on LPC P0.9
	T3MCR |= (1 << 1);	// Set Reset on MR0, TC will be reset if MR0 matches it
	T3EMR |= (3 << 4); // Toggle on match EMC0
	T3CTCR &= ~(1 << 0);
	T3CTCR &= ~(1 << 1);

}

/**
 * Configure Timer 3 for frequency generation
 */
void configT3MR0(int freq) {

	timer3Start();
	timer0Reset();			// Reset Timer 0
	T3MR0 = (1000000 / (2 * freq));	// load T3MR0 with match value based on frequency PCLK/(2*freq)
	timer3Reset();

}
