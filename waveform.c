#include "final.h"

int waveTable[256];

extern void fillWaveTable(void) {
	for (int i = 0; i < 256; i++) {
		waveTable[i] = (500)*(1+sin(2*3.14159265*i/256.0));
	}
}
/*
 * We need to determine what value to enter for the desired frequencies
 */
extern void triangleWave(int count, int step) {
	for (int i = 0; i < count; i = i + step) {
		DACR = i << 6;
		wait_us(10);
	}
	for (int i = count; i > 0; i = i - step) {
		DACR = i << 6;
		wait_us(10);
	}
}

extern void sineWave(int freq) {
	int i;
	for (i = 0; i < 256; i = i + 10) {
		DACR = ((int) waveTable[i]) << 6;
		wait_us(freq);
	}
}
