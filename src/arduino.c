#include "arduino.h"

// led location on LPC810 mini-kit
// http://www.lpcware.com/lpc800-mini-kit
#define LED_LOCATION    (2)

void pinMode(uint8_t pin, uint8_t mode)
{
	// check if it is Arduino Uno LED pin
	if(pin==13)
	{
	    if(mode==OUTPUT) LPC_GPIO_PORT->DIR0 |= (1 << LED_LOCATION);
	}
}
void digitalWrite(uint8_t pin, uint8_t value)
{
	// check if it is Arduino uno LED pin
	if(pin==13)
	{
		if(value==1) LPC_GPIO_PORT->SET0 = 1 << LED_LOCATION;
		else LPC_GPIO_PORT->CLR0 = 1 << LED_LOCATION;
	}
}

void delay(uint32_t milliSeconds)
{
	mrtDelay(milliSeconds);
}
