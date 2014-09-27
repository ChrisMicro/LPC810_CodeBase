/********************************************************************************
 *
 * integer sin function speed test programm
 *
 ********************************************************************************/
#include "arduino.h"
#include "sin_int16.h"

void setup() {
  Serial_begin(9600);
}

#define CYCLES 65535

void loop() {
  Serial_print("calculating ");
  Serial_printnumber(CYCLES);
  Serial_print(" sin values");
  unsigned int n;

  unsigned long start=millis();
  for(n=0;n<CYCLES;n++)
  {
    volatile int x=sin_int16(n);
  }
  unsigned long stop=millis();
  unsigned long duration=stop-start;
  Serial_print(" time usage:");
  Serial_printnumber(duration);
  Serial_println("ms");
  Serial_printnumber(duration*1000/CYCLES);
  Serial_print(".");
  Serial_printnumber((duration*10000/CYCLES)%10);
  Serial_println("us per sine calculation");
  delay(1000);
}
