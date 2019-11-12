#include "registerDef.h"
#ifndef TIMER_H
#define TIMER_H



/**
 *  Start Timer 0
 */
static inline void timer0Start() {
	T0TCR |= (1 << 0);
}

/**
 * Initialize Timer 0
 */
void timer0Init() {
	PCONP |= (1 << 1);			// Timer 0 Enable
	PCLKSEL0 &= ~(3 << 2);	// Reset clock selection on Timer 0, default = 1MHz
	timer0Start();
}

/**
 * Stop Timer 0
 */
static inline void timer0Stop() {
	T0TCR &= ~(1 << 0);
}

/**
 * Clear Timer 0 Counter
 */
static inline void timer0Reset() {
	T0TCR |= (1 << 1);
	while (T0TC != 0) {
		// wait until timer has changed
	}
	T0TCR &= ~(1 << 1);	//
}


/**
 * Read Timer 0
 */
static inline int timer0Read_us(void) {
	return T0TC; // Read Timer 0 Counter
}


/**
 *  True read Timer 0 for floating value in DACR conversion
 */
static inline float timer0Read(void) {
	return timer0Read_us() / 1000000.0;
}


/**
 * wait function in microseconds
 */
void wait_us(float usec) {
	timer0Start();
	timer0Reset();
	while (timer0Read_us() < usec) {
	}
}


/**
 * wait function in seconds
 */
void wait(float sec) {
	wait_us(sec * 1000000);
}


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
	T2TCR &= ~(1 << 1);	//
}



#endif // timer_H
