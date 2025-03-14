#include "final.h"

/**
 * Start Timer 2
 */
static inline void timer2Start() {

	T2TCR |= (1 << 0);

}

/**
 * Reset Timer 2
 */
static inline void timer2Reset() {

	T2TCR |= (1 << 1);
	while (T2TC != 0) {
		// wait until timer has changed
	}

	T2TCR &= ~(1 << 1);

}

/*
 * Stop Timer 0
 */
void timer2Stop() {

	T2TCR &= ~(1 << 0);

}

/**
 * Initialize Timer 2 to control the timing of decay for each tone
 */
void timer2Init() {
	PCONP |= (1 << 22);		// Timer 2 Enable
	PCLKSEL1 &= ~(1 << 12); // Reset clock selection on Timer 2, default = 1MHz
	PCLKSEL1 &= ~(1 << 13); // Reset clock selection on Timer 2, default = 1MHz
	PINSEL0 |= (1 << 18);	// Select Timer 2, Match register 3 on LPC P0.9
	PINSEL0 |= (1 << 19); // Select Timer 2, Match register 3 on LPC P0.9
	T2MCR |= (1 << 10);	// Set Reset on MR3, TC will be reset if MR3 matches it
	T2EMR |= (3 << 10); // Toggle on match EMC3
	T2CTCR &= ~(1 << 0);
	T2CTCR &= ~(1 << 1);

}

/**
 * Configure Timer 2 for square wave generation
 */
void configT2MR3(int freq) {
	timer2Start();
	timer0Reset();			// Reset Timer 0
	T2MR3 = (1000000 / (2 * freq));	// load T2MR3 with match value based on frequency PCLK/(2*freq)
	timer2Reset();
	while (timer0Read_us() < 100000.0) {
	}
}
