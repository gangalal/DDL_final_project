#include "registerDef.h"
#ifndef TIMER0_H
#define TIMER0_H

/*
 * Initialize timer 0
 */
void timer0Init() {
	PCONP |= (1 << 1);					// Timer 0 Enable
	PCLKSEL0 &= ~ (3 << 2);				// Reset clock selection on Timer 0, default = 1MHz
}

/*
 * Start Timer 0
 */
void timer0Start() {

	T0TCR |= (1 << 0);

}

/*
 * Stop Timer 0
 */
void timer0Stop() {

	T0TCR &= ~(1 << 0);

}

/*
 * Clear Timer 0
 */
void timer0Reset() {

	T0TCR |= (1 << 1);
	while (T0TC != 0) {
		// wait until timer has changed
	}
	T0TCR &= ~(1 << 1);	//

}

/*
 * Read Timer 0
 */
int timer0Read_us() {

	return T0TC; // Read Timer 0 Counter

}

/*
 * Wait function for Timer 0 in microseconds
 */
void wait_us(int usec) {

	timer0Start();
	timer0Reset();
	while(timer0Read_us() < usec) {
	}
}

/*
 * wait function for Timer 0
 */
void wait_ticks(unsigned long count) {
	volatile int ticks;
	for (ticks = 0; ticks < count; ticks++) {
		// do nothing
		for (int i = 0; i<256; i++)
		{

		}
	}

}

/**
 * wait function of one second for Timer 0
 */
void waitOneSecond(unsigned long count) {
	volatile int ticks;
	volatile int temp = 157142 * count;
	for (ticks = 0; ticks < temp; ticks++) {

	}
}

#endif // timer0_H
