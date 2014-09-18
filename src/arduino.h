#include <stdio.h>
#include "LPC8xx.h"
#include "gpio.h"
#include "mrt.h"
#include "uart.h"
#include "adc.h"
#include "sct.h"

#define INPUT 	0
#define OUTPUT 	1
#define LOW 	0
#define HIGH 	1

// adc
#define A1 1 // channel 1

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t value);
void digitalToggle(uint8_t Pin);
int digitalRead(uint8_t pin);
void Serial_begin(uint32_t baudRate);
void Serial_print(char * string);
void Serial_println(char * string);
void Serial_printnumber(uint32_t number);
uint32_t millis();
void delay(unsigned long ms);
uint16_t analogRead(uint8_t channel );
void analogWrite(uint8_t analogOutPin, uint16_t value);
int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

