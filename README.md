
LPC810_CodeBase providing some basic Arduino functions
======================================================

The Arduino Sketch should be place in the file

sketch_ino.c

It is important that the first line in this file is

#include "sketch_ino.h"

currently implemented arduino functions:

  pinMode
  digitalWrite
  digitalRead
  delay
  Serial_begin
  Serial_print
  Serial_println
  Serial_printnumber
  millis
  analogRead

     LPC800 Pining ( Arduino pin numbering )
     =======================================
                      ________
                      |   U   |
          reset      -|       |- digital 0 / analog in 0 / RX
     TX / digital 4  -|  LPC  |- GND
          digital 3  -|  810  |- +3.3V
          digital 2  -|       |- digital 1 / analog in 1
                      |_______|


How to install the ARM Tool chain on Ubuntu 12.04 : https://launchpad.net/~terry.guo/+archive/ubuntu/gcc-arm-embedded



