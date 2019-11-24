/*
 * registerDef.h
 *
 *  Created on: Nov 14, 2019
 *      Author: lama0003
 */

#ifndef REGISTERDEF_H_
#define REGISTERDEF_H_

#define PCONP (*(volatile unsigned int *)(0x400FC0C4))
#define PCLKSEL0 (*(volatile unsigned int *)(0x400FC1A8)) 	// Timer 0 Clock select
#define PCLKSEL1 (*(volatile unsigned int *)(0x400FC1AC)) 	// Timer 2 Clock select

#define PINSEL0 (*(volatile unsigned int *)(0x4002C000))
#define PINSEL1 (*(volatile unsigned int *)(0x4002C004))
#define PINMODE0 (*(volatile unsigned int *)(0x4002C040))
#define PINMODE1 (*(volatile unsigned int *)(0x4002c044))

#define T0TCR (*(volatile unsigned int *)(0x40004004)) 		// Timer 0
#define T0TC (*(volatile unsigned int *)(0x40004008))		// Timer Counter

#define FIO0DIR (*(volatile unsigned int *)(0x2009c000))
#define FIO0PIN (*(volatile unsigned int *)(0x2009c014))
#define FIO2DIR (*(volatile unsigned int *)(0x2009c040))
#define FIO2PIN (*(volatile unsigned int *)(0x2009c054))
#define FIO2PIN0 (*(volatile unsigned char *)(0x2009C054))

#define T2TCR (*(volatile unsigned int *)(0x40090004)) 		// Timer 2 Timer Control Register
#define T2TC (*(volatile unsigned int *)(0x40090008)) 		// Timer 2 Timer Counter
#define T2EMR (*(volatile unsigned int *)(0x4009003C)) 		// EMR Match Register for Timer 2
#define T2MCR (*(volatile unsigned int *)(0x40090014)) 		// MCR Match Register for Timer 2
#define T2CTCR (*(volatile unsigned int *)(0x40090070)) 	// Count Control Register for Timer 2 Selects between timer and counter mode
#define T2MR3 (*(volatile unsigned int *)(0x40090024)) 		// Match Register 3

#define DACR (*(volatile unsigned int *)(0x4008C000)) 		// DAC Register

#define U0LCR (*(volatile unsigned int *)(0x4000C00C))
#define U0DLL (*(volatile unsigned int *)(0x4000C000))
#define U0DLM (*(volatile unsigned int *)(0x4000C004))
#define U0FDR (*(volatile unsigned int *)(0x4000C028)) //fractional dividing register
#define U0FCR (*(volatile unsigned int *)(0x4000C008))
#define U0ACR (*(volatile unsigned int *)(0x4000C020))
#define U0RBR (*(volatile unsigned int *)(0x4000C000))
#define U0LSR (*(volatile unsigned int *)(0x4000C014))

#endif /* REGISTERDEF_H_ */
