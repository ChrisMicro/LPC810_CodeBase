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

void delay(uint32_t milliSeconds)
{
	mrtDelay(milliSeconds);
}
