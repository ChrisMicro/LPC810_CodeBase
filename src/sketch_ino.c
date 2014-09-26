#include "arduino.h"
/*
  sigma delta modulator experiments

  generate a pseudo analog sine wave on a digital pin output
  with the sigmal delta principle

  14.4.2013 initial version, ch alias ChrisMicro
  26.9.2014 modified for LPC810, ChrisMicro

  created 2013
  by ChrisMicro

  This example code is in the public domain.

  for more sigma delta examples see
  http://hobby-roboter.de/forum/viewtopic.php?f=5&t=141

  hardware:
  connect a low pass filter to the speaker output pin.
  low pass:  470Ohm, 100nF
  or 470Ohm, 10nF for lower impedance

*/
//#define CHIRP // uncomment this line to get a chirp signal
int speakerPin=3;
int ledPin=2;

int8_t sintab[256]=
{
  0 ,3 ,6 ,9 ,12 ,15 ,18 ,21 ,24 ,27 ,30 ,33 ,36 ,39 ,42 ,45 ,48 ,51 ,54 ,57 ,59 ,62 ,65 ,67 ,70 ,73 ,75 ,78 ,80 ,82 ,85 ,87 ,
  89 ,91 ,94 ,96 ,98 ,100 ,102 ,103 ,105 ,107 ,108 ,110 ,112 ,113 ,114 ,116 ,117 ,118 ,119 ,120 ,121 ,122 ,123 ,123 ,124 ,125 ,
  125 ,126 ,126 ,126 ,126 ,126 ,127 ,126 ,126 ,126 ,126 ,126 ,125 ,125 ,124 ,123 ,123 ,122 ,121 ,120 ,119 ,118 ,117 ,116 ,114 ,
  113 ,112 ,110 ,108 ,107 ,105 ,103 ,102 ,100 ,98 ,96 ,94 ,91 ,89 ,87 ,85 ,82 ,80 ,78 ,75 ,73 ,70 ,67 ,65 ,62 ,59 ,57 ,54 ,51 ,
  48 ,45 ,42 ,39 ,36 ,33 ,30 ,27 ,24 ,21 ,18 ,15 ,12 ,9 ,6 ,3 ,0 ,-3 ,-6 ,-9 ,-12 ,-15 ,-18 ,-21 ,-24 ,-27 ,-30 ,-33 ,-36 ,-39 ,
  -42 ,-45 ,-48 ,-51 ,-54 ,-57 ,-59 ,-62 ,-65 ,-67 ,-70 ,-73 ,-75 ,-78 ,-80 ,-82 ,-85 ,-87 ,-89 ,-91 ,-94 ,-96 ,-98 ,-100 ,-102 ,
  -103 ,-105 ,-107 ,-108 ,-110 ,-112 ,-113 ,-114 ,-116 ,-117 ,-118 ,-119 ,-120 ,-121 ,-122 ,-123 ,-123 ,-124 ,-125 ,-125 ,-126 ,
  -126 ,-126 ,-126 ,-126 ,-127 ,-126 ,-126 ,-126 ,-126 ,-126 ,-125 ,-125 ,-124 ,-123 ,-123 ,-122 ,-121 ,-120 ,-119 ,-118 ,-117 ,
  -116 ,-114 ,-113 ,-112 ,-110 ,-108 ,-107 ,-105 ,-103 ,-102 ,-100 ,-98 ,-96 ,-94 ,-91 ,-89 ,-87 ,-85 ,-82 ,-80 ,-78 ,-75 ,-73 ,
  -70 ,-67 ,-65 ,-62 ,-59 ,-57 ,-54 ,-51 ,-48 ,-45 ,-42 ,-39 ,-36 ,-33 ,-30 ,-27 ,-24 ,-21 ,-18 ,-15 ,-12 ,-9 ,-6 ,-3
};

void setup() {
  // initialize the digital pin as an output.
  pinMode(speakerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

int32_t integrator=0;
int32_t dacValue=64;
int32_t oldValue=0;
uint16_t phase=0;
uint16_t phaseDelta=200*49;
uint16_t n;

// the DAC input range goes from
#define MINDACVALUE -128
// to
#define MAXDACVALUE 127
// the DAC value is scaled to the microcontroller
// digital output voltage e.g. from 0 to 3.3 V

#define NSTEPS_TIL_DAC_UPDATE 200

void loop() {

  // sin wave DDS ( direct digital synthesis )
  dacValue=sintab[phase>>8];
  phase+=phaseDelta;

  #ifdef CHIRP
    phaseDelta++;
  #endif

  // sigma delta DAC, hold the DAC value for n-steps constant
  // and do sigma delta
  for(n=0;n<NSTEPS_TIL_DAC_UPDATE;n++)
  {
    integrator+=dacValue-oldValue; // sigma+=delta
    if(integrator>0)
    {
      digitalWrite(speakerPin, HIGH);
      oldValue=MAXDACVALUE;
    }
    else
    {
      digitalWrite(speakerPin, LOW);
      oldValue=MINDACVALUE;
    }
  }
}
/*

     LPC800 Pining ( Arduino pin numbering )
     =======================================
                      ________
                      |   U   |
          reset      -|       |- digital 0 / analog in A0 / RX
     TX / digital 4  -|  LPC  |- GND
          digital 3  -|  810  |- +3.3V
          digital 2  -|       |- digital 1 / analog in A1
                      |_______|


     Mini Kit Board ( http://www.lpcware.com/lpc800-mini-kit )
     =========================================================
                      ________
                      |   U   |
        reset switch -|       |- RX
                  TX -|  LPC  |- GND
             speaker -|  810  |- +3.3V
            test led -|       |- ISP switch
                      |_______|

 */



