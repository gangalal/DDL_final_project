/*
 ===============================================================================
 Name        : FinalProject.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
 ===============================================================================
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

#include <stdio.h>
#include <math.h>
#include "Util.h"
#include "timer.h"

#define FIO2DIR (*(volatile unsigned int *)0x2009c040)
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)

void GPIOInit() {
	FIO2DIR |= (1 << 0); // configure P2[0] as output
	FIO2DIR |= (1 << 1);
	FIO2DIR |= (1 << 2);
	FIO2DIR |= (1 << 3);
	FIO2DIR |= (1 << 4);
	FIO2DIR |= (1 << 5);
	FIO2DIR |= (1 << 6);
	FIO2DIR |= (1 << 7);
	FIO2DIR |= (1 << 8);
	FIO2DIR |= (1 << 11);

	FIO2PIN &= ~(1 << 0); //set P2[0] low
	FIO2PIN &= ~(1 << 1);
	FIO2PIN &= ~(1 << 2);
	FIO2PIN &= ~(1 << 3);
	FIO2PIN &= ~(1 << 4);
	FIO2PIN &= ~(1 << 5);
	FIO2PIN &= ~(1 << 6);
	FIO2PIN &= ~(1 << 7);
	FIO2PIN &= ~(1 << 8);
	FIO2PIN &= ~(1 << 11);
}


void sendInit() {
	FIO2PIN |= (0 << 0);
	FIO2PIN |= (0 << 1);
	FIO2PIN |= (1 << 2);
	FIO2PIN |= (1 << 3);
	FIO2PIN |= (1 << 4);
	FIO2PIN |= (0 << 5);
	FIO2PIN |= (0 << 6);
	FIO2PIN |= (0 << 7);
	FIO2PIN |= (1 << 11); //Rs 1
}

void sendComand() {
	FIO2PIN |= (0 << 0);
	FIO2PIN |= (0 << 1);
	FIO2PIN |= (0 << 2);
	FIO2PIN |= (0 << 3);
	FIO2PIN |= (0 << 4);
	FIO2PIN |= (0 << 5);
	FIO2PIN |= (0 << 6);
	FIO2PIN |= (1 << 7);
	FIO2PIN &= ~(1 << 11); //Rs low
}

int main(void) {
	GPIOInit();
	sendInit();
	wait_us(100);
	sendComand();
	FIO2PIN |= (1 << 8); //E high
	FIO2PIN &= ~(1 << 8); // E low
	wait_us(100);
	while (1) {
    printf("hello world\n");
	}
	return 0;
}
