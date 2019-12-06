#ifndef REGISTERDEF_H_
#define REGISTERDEF_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PCONP (*(volatile unsigned int *)(0x400FC0C4))
#define PCLKSEL0 (*(volatile unsigned int *)(0x400FC1A8))   // Timer 0, 1 Clock select
#define PCLKSEL1 (*(volatile unsigned int *)(0x400FC1AC))   // Timer 2, 3 Clock select

#define PINSEL0 (*(volatile unsigned int *)(0x4002C000))
#define PINSEL1 (*(volatile unsigned int *)(0x4002C004))
#define PINMODE0 (*(volatile unsigned int *)(0x4002C040))
#define PINMODE1 (*(volatile unsigned int *)(0x4002C044))

#define FIO0DIR (*(volatile unsigned int *)(0x2009c000))
#define FIO0PIN (*(volatile unsigned int *)(0x2009c014))
#define FIO2DIR (*(volatile unsigned int *)0x2009c040)      // GPIO 2
#define FIO2PIN (*(volatile unsigned int *)0x2009c054)
#define FIO2PIN0 (*(volatile unsigned char *)0x2009C054)

#define I2CPADCFG (*(volatile unsigned int *)(0x4002C07C))  // I2C for EEProm
#define I2C0SCLH (*(volatile unsigned int *)(0x4001C010))
#define I2C0SCLL (*(volatile unsigned int *)(0x4001C014))
#define I2C0CONSET (*(volatile unsigned int *)(0x4001C000))
#define I2C0CONCLR (*(volatile unsigned int *)(0x4001C018))
#define I2C0DAT (*(volatile unsigned int *)(0x4001C008))

#define T0TCR (*(volatile unsigned int *)(0x40004004))      // Timer 0
#define T0TC (*(volatile unsigned int *)(0x40004008))       // Timer Counter

#define T1TCR (*(volatile unsigned int *)(0x40008004))		// Timer 1
#define T1TC (*(volatile unsigned int *)(0x40008008))		// Timer Counter

#define T2TCR (*(volatile unsigned int *)(0x40090004))      // Timer 2 Timer Control Register
#define T2TC (*(volatile unsigned int *)(0x40090008))       // Timer 2 Timer Counter
#define T2EMR (*(volatile unsigned int *)(0x4009003C))      // EMR Match Register for Timer 2
#define T2MCR (*(volatile unsigned int *)(0x40090014))      // MCR Match Register for Timer 2
#define T2CTCR (*(volatile unsigned int *)(0x40090070))     // Count Control Register for Timer 2 Selects timer/counter mode
#define T2MR3 (*(volatile unsigned int *)(0x40090024))      // Timer 2 Match Register 3
#define T2MR2 (*(volatile unsigned int *)(0x40090020))      // Timer 2 Match Register 2

#define T3TCR (*(volatile unsigned int *)(0x40094004))		// Timer 3 Timer Control Register
#define T3TC (*(volatile unsigned int *)(0x40094008))		// Timer 3 Timer Counter
#define T3EMR (*(volatile unsigned int *)(0x4009403C))		// EMR Match Register for Timer 3
#define T3MCR (*(volatile unsigned int *)(0x40094014))		// MCR Match Register for Timer 3
#define T3CTCR (*(volatile unsigned int *)(0x40094070))		// Count Control Register for Timer 3 - selects timer/counter Mode
#define T3MR0 (*(volatile unsigned int *)(0x40094018))		// Timer 3 Match Register 0

#define DACR (*(volatile unsigned int *)(0x4008C000))       // DAC Register

#define U0LCR (*(volatile unsigned int *)(0x4000C00C))
#define U0DLL (*(volatile unsigned int *)(0x4000C000))
#define U0DLM (*(volatile unsigned int *)(0x4000C004))
#define U0FDR (*(volatile unsigned int *)(0x4000C028))      //fractional dividing register
#define U0FCR (*(volatile unsigned int *)(0x4000C008))
#define U0ACR (*(volatile unsigned int *)(0x4000C020))
#define U0TER (*(volatile unsigned int *)(0x4000C030))
#define U0LSR (*(volatile unsigned int *)(0x4000C014))
#define U0RBR (*(volatile unsigned int *)(0x4000c000))

#endif /* REGISTERDEF_H_ */
