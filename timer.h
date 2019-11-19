#include "registerDef.h"
#ifndef TIMER_H
#define TIMER_H

// This timer generates our waveform
void timer0Init() {
	PCONP |= (1 << 1);					// Timer 0 Enable
	PCLKSEL0 &= ~ (3 << 2);				// Reset clock selection on Timer 0, default = 1MHz
}

// Start Timer 0
void timer0Start() {

	T0TCR |= (1 << 0);

}

// Stop Timer 0
void timer0Stop() {

	T0TCR &= ~(1 << 0);

}

// Clear Counter
 void timer0Reset() {

	T0TCR |= (1 << 1);
	while (T0TC != 0) {
		// wait until timer has changed
	}
	T0TCR &= ~(1 << 1);	//

}

 int timer0Read_us() {

	return T0TC; // Read Timer 0 Counter

}

void wait_us(int usec) {

	timer0Start();
	timer0Reset();
	while(timer0Read_us() < usec) {
	}
}



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
 * waits for count*1sec
 */
void waitOneSecond(unsigned long count) {
	volatile int ticks;
	volatile int temp = 157142 * count;
	for (ticks = 0; ticks < temp; ticks++) {

	}
}


#endif // timer_H
