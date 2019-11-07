#ifndef TIMER_H
#define TIMER_H

#define PCONP (*(volatile unsigned int *)(0x400FC0C4))
#define PCLKSEL0 (*(volatile unsigned int *)(0x400FC1A8)) 	// Timer 0 Clock select
#define PCLKSEL1 (*(volatile unsigned int *)(0x400FC1AC)) 	// Timer 2 Clock select

#define PINSEL0 (*(volatile unsigned int *)(0x4002C000))
#define PINSEL1 (*(volatile unsigned int *)(0x4002C004))
#define PINMODE0 (*(volatile unsigned int *)(0x4002C040))

#define T0TCR (*(volatile unsigned int *)(0x40004004)) 		// Timer 0
#define T0TC (*(volatile unsigned int *)(0x40004008))		// Timer Counter


// This timer generates our waveform
void timerInit0() {
	PCONP |= (1 << 1);					// Timer 0 Enable
	PCLKSEL0 &= ~ (3 << 2);				// Reset clock selection on Timer 0, default = 1MHz
}

// Start Timer 0
static inline void timerStart() {

	T0TCR |= (1 << 0);

}

// Stop Timer 0
static inline void timerStop() {

	T0TCR &= ~(1 << 0);

}

// Clear Counter
static inline void timerReset() {

	T0TCR |= (1 << 1);
	while (T0TC != 0) {
		// wait until timer has changed
	}
	T0TCR &= ~(1 << 1);	//

}

static inline int timerRead_us() {

	return T0TC; // Read Timer 0 Counter

}

void wait_us(int usec) {

	timerStart();
	timerReset();
	while(timerRead_us() < usec) {
	}
}



void wait_ticks(unsigned long count) {
	volatile int ticks;
	for (ticks = 0; ticks < count; ticks++) {
		// do nothing
	}

}


/**
 * waits for count*1sec
 */
void waitOneSecond(unsigned long count) {
	volatile int ticks;
	volatile int temp = 157142 * count;
	for (ticks = 0; ticks < temp; ticks++) {

	}
}


#endif // timer_H
