#include <stdio.h>
#include "LPC8xx.h"
#include "gpio.h"
#include "mrt.h"
#include "uart.h"

#define INPUT 	0
#define OUTPUT 	1
#define LOW 	0
#define HIGH 	1

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
int digitalRead(uint8_t pin);
void delay(uint32_t milliSeconds);
