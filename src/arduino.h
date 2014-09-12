#include <stdio.h>
#include "LPC8xx.h"
#include "gpio.h"
#include "mrt.h"
#include "uart.h"
#include "adc.h"

#define INPUT 	0
#define OUTPUT 	1
#define LOW 	0
#define HIGH 	1

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
int digitalRead(uint8_t pin);
void delay(uint32_t milliSeconds);
void Serial_begin(uint32_t baudRate);
void Serial_print(char * string);
void Serial_println(char * string);
void Serial_printnumber(uint32_t number);
uint32_t millis();
uint16_t analogRead(uint8_t channel );
