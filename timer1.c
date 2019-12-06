#include "final.h"

/*
 * Initialize timer 0
 */
void timer1Init() {
	PCONP |= (1 << 2);					// Timer 1 Enable
	PCLKSEL0 &= ~ (3 << 4);				// Reset clock selection on Timer 1, default = 1MHz
}

/*
 * Start Timer 0
 */
void timer1Start() {

	T1TCR |= (1 << 0);

}

/*
 * Stop Timer 0
 */
void timer1Stop() {

	T1TCR &= ~(1 << 0);

}

/*
 * Clear Timer 0
 */
void timer1Reset() {

	T1TCR |= (1 << 1);
	while (T1TC != 0) {
		// wait until timer has changed
	}
	T1TCR &= ~(1 << 1);	//

}

/*
 * Read Timer 0
 */
int timer1Read_us() {

	return T1TC; // Read Timer 0 Counter

}

/*
 * Wait function for Timer 0 in microseconds
 */
void wait1_us(int usec) {

	timer1Start();
	timer1Reset();
	while(timer1Read_us() < usec) {

	}

}
