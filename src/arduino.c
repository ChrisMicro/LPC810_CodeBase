/**************************************************************************/
/*!
    @file     arduino.c
    @author   ChrisMicro
    @author   others ( marked in code )
    @brief    arduino compatible functions for LPC810

    @section LICENSE see below for my code contribution

*/
/**************************************************************************/
#include "arduino.h"

// led location on LPC810 mini-kit
// http://www.lpcware.com/lpc800-mini-kit
#define LED_LOCATION    (2)
/* Pin setup generated via Switch Matrix Tool
   ------------------------------------------------
   Package	Logic	 Function
   =======  =====    ========
   PIN1		PIO0_5 = RESET 			// not usable
   PIN2		PIO0_4 = U0_TXD
   PIN3		PIO0_3 = GPIO
   PIN4		PIO0_2 = GPIO 			// User LED
   PIN5		PIO0_1 = GPIO			// ISP Switch
   PIN8		PIO0_0 = U0_RXD
   ------------------------------------------------
   NOTE: SWD is disabled to free GPIO pins!
   ------------------------------------------------ */

void pinMode(uint8_t pin, uint8_t mode)
{
	// check if it is Arduino Uno LED pin
	if(pin==13)
	{
	    if(mode==OUTPUT) LPC_GPIO_PORT->DIR0 |= (1 << LED_LOCATION);
	    else LPC_GPIO_PORT->DIR0 &= ~(1 << LED_LOCATION);
	}else
	{
		if(mode==OUTPUT) LPC_GPIO_PORT->DIR0 |= (1 << pin);
		else LPC_GPIO_PORT->DIR0 &= ~(1 << pin);
	}
}
void digitalWrite(uint8_t pin, uint8_t value)
{
	// check if it is Arduino uno LED pin
	if(pin==13)
	{
		if(value==1) LPC_GPIO_PORT->SET0 = 1 << LED_LOCATION;
		else LPC_GPIO_PORT->CLR0 = 1 << LED_LOCATION;
	}else
	{
		if(value==1) LPC_GPIO_PORT->SET0 = 1 << pin;
		else LPC_GPIO_PORT->CLR0 = 1 << pin;
	}
}

int digitalRead(uint8_t pin)
{
	int result=0;
	if (LPC_GPIO_PORT->PIN0 & (0x1 << pin))
	{
	  result = 1;
	}
	return result;
}
/*
void delay(uint32_t milliSeconds)
{
	mrtDelay(milliSeconds);
}
*/
/*
 * from wiring.c
 * https://code.google.com/p/arduino/source/browse/trunk/hardware/arduino/cores/arduino/wiring.c
 *
 *   wiring.c - Partial implementation of the Wiring API for the ATmega8.
 * Part of Arduino - http://www.arduino.cc/
 *
 * Copyright (c) 2005-2006 David A. Mellis
 */

void delay(unsigned long ms)
{
	uint32_t start = (uint32_t)micros(); // changed to uint32 / ChrisMicro

	while (ms > 0) {
		if (((uint32_t)micros() - start) >= 1000) {
			ms--;
			start += 1000;
		}
	}
}
/*
 * The syntax for real Arduinos would be
 * Serial.begin(9600);
 *
 * Because the LPC810 software is not written in c++,
 * we can not use the "."
 * We use "_" instead which results in a slitly incompatile library.
 *
 */
void Serial_begin(uint32_t baudRate)
{
	uart0Init(baudRate);
}
/*
 * Serial_print can only print text, not numbers
 * due to the lack auf c++
 */
void Serial_print(char * string)
{
	printf("%s",string);
}
void Serial_println(char * string)
{
	printf("%s\n\r",string);
}
void Serial_printnumber(uint32_t number)
{
	printf("%d ",number);
}

uint16_t analogRead(uint8_t channel )
{
	static uint8_t initFlags=0;

	uint16_t value=0;

	if((initFlags&(1<<channel))==0)
	{
		init_adc(channel);
		initFlags|=1<<channel;
	}

	return 	read_adc(channel);;
}

/******************************************************************************

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	1. Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.
	2. Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in the
	documentation and/or other materials provided with the distribution.
	3. Neither the name of the copyright holders nor the
	names of its contributors may be used to endorse or promote products
	derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ''AS IS'' AND ANY
	EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*************************************************************************/
