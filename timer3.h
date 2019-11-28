/*
 * timer3.h
 *
 *  Created on: Nov 26, 2019
 *      Author: lama0003
 */

#ifndef TIMER3_H_
#define TIMER3_H_

/**
 * Start Timer 2
 */
static inline void timer3Start() {
	T3TCR |= (1 << 0);
}

/**
 * Reset Timer 2
 */
static inline void timer3Reset() {
	T3TCR |= (1 << 1);
	while (T3TC != 0) {
		// wait until timer has changed
	}
	T3TCR &= ~(1 << 1);	//
}

int timer3Read_us() {

	return T0TC; // Read Timer 0 Counter

}

void wait3_us(int usec) {

	timer3Start();
	timer3Reset();
	while (timer3Read_us() < usec) {
	}
}

/**
 * Initialize Timer 2 to control the timing of decay for each tone
 */
void timer3Init() {
	PCONP |= (1 << 23);		// Timer 2 Enable
	PCLKSEL1 &= ~(1 << 14); // Reset clock selection on Timer 2, default = 1MHz
	PCLKSEL1 &= ~(1 << 15); // Reset clock selection on Timer 2, default = 1MHz
	PINSEL0 |= (1 << 20);	// Select Timer 2, Match register 3 on LPC P0.9
	PINSEL0 |= (1 << 21); // Select Timer 2, Match register 3 on LPC P0.9
	T3MCR |= (1 << 1);	// Set Reset on MR3, TC will be reset if MR3 matches it
	T3EMR |= (3 << 4); // Toggle on match EMC3
	T3CTCR &= ~(1 << 0);
	T3CTCR &= ~(1 << 1);

}

/**
 * Configure Timer 2 for frequency generation
 */
void configT3MR0(int freq) {
	timer3Start();
	timer0Reset();			// Reset Timer 0
	T3MR0 = (1000000 / (2 * freq));	// load T2MR3 with match value based on frequency PCLK/(2*freq)
	timer3Reset();
	while (timer0Read_us() < 1000000.0) {
	}
}

/*
*
 * Configure Timer 3 for frequency generation

void configT3MR0(int freq) {
	timer3Start();
	timer0Reset();			// Reset Timer 0
	T3MR0 = (1000000 / (2 * freq));	// load T2MR3 with match value based on frequency PCLK/(2*freq)
	timer3Reset();
}
*/


#endif /* TIMER3_H_ */
