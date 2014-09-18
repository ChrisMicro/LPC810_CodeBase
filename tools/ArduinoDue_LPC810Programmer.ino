/*
 LPC810 serial programmer with an Arduino DUE
 
 The Arduino DUE has several serial ports.
 With these ports you can receive data from the PC and feed it to the LPC810.
 It is simple to use an Arduino Due as Programming Adapter for an LPC810.
 Because the Arduino Due works with 3.3V it is possible to connect it directly 
 to the LPC810. No level shifters are needed.

 A little software is necessary to receive the data from the PC and put it on 
 another serial port on the Arduino Due.
 It is quite comfortable that the Due has so many pins an can control the ISP 
 and the RESET line of the LPC.
 With this connection, the Due can bring the LPC in the ISP mode, program it 
 and make a reset afterwards so that the new program on the LPC is starting 
 automatically.

 You may use 'flushmagig.py" as download software for the LPC810.
 
 For Ubuntu the command line using flushmagic could look as follows:
 
 ./flushmagic.py /dev/ttyACM0 blinky.bin


 @author ChrisMicro
 @copyright (c) 2014 ChrisMicro
 
  Software License Agreement (BSD License)
 
 */
 
// Arduino Due Pining
#define LEDPIN           13      // programming indicator
#define LPC_RESET         8      // arduino pin connected to LPC810 reset
#define LPC_ISP           9      // arduino pin connected to LPC810 ISP mode pin
#define ARDUINO_RXPIN    19      // data from LPC to arduino
#define ARDUINO_TXPIN    18      // data from arduino to LPC

#define LEDON  { digitalWrite(LEDPIN,HIGH); } 
#define LEDOFF { digitalWrite(LEDPIN,LOW); }


void resetLPC()
{ 
  pinMode(LPC_RESET,OUTPUT); 
  digitalWrite(LPC_RESET,LOW);
  delayMicroseconds(100);
  digitalWrite(LPC_RESET,HIGH);
  pinMode(LPC_RESET,INPUT_PULLUP);
}

void setLpcIspMode()
{
  pinMode(LPC_ISP,OUTPUT);
  digitalWrite(LPC_ISP,LOW); 
  delayMicroseconds(100);
  resetLPC();
  delayMicroseconds(100);
  digitalWrite(LPC_ISP,HIGH);
  pinMode(LPC_ISP,INPUT_PULLUP);
}

#define LPCRUNNING_STATE 1
#define LPCPROGRAMMING_STATE 0

uint8_t state=LPCPROGRAMMING_STATE;
unsigned long stopTime;
#define TIMEOUT_MS 2000

void setup() 
{
  // initialize both serial ports:
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(LEDPIN,OUTPUT);
  LEDON;
  
  setLpcIspMode();
  
  stopTime=millis()+TIMEOUT_MS;
}


void loop() 
{  
  // read from pc serial port, send to LPC:
  if (Serial.available()) 
  {
    uint8_t value = Serial.read();
    Serial1.write(value);
    stopTime=millis()+TIMEOUT_MS;
  }
  
  if(state==LPCPROGRAMMING_STATE)
  {
    if(millis()>stopTime)
    {
       LEDOFF;
       resetLPC();
       state=LPCRUNNING_STATE;
    }
  }

  // read from LPC, send to PC:
  if (Serial1.available()) 
  {
    uint8_t value = Serial1.read();
    Serial.write(value);
  }
 
}
/***************************************************************************
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
*/
/**************************************************************************/
