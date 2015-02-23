/*
nRF24 simple message reciever

Last modified: 2015 02 23

Listens for any traffic and prints it out to the serial terminal.
This code does not have transmitting capabilities.

For use with Nordic Semiconducor nRF24L01 2.4GHz which communicates wit the Arduino over SPI.
http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24L01

SPI Pinouts: 
See http://arduino.cc/en/Reference/SPI for more details.
Pin     Arduino UNO (328)   Arduino MEGA (2560)
 VCC      3.3V                3.3V
 GND      GND                  GND
 CE         9                  9
 CSN       10                  10
 MOSI      11                  51
 MISO      12                  50
 SCK       13                  52

*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

char text[32];  //Receive buffer

// Setup radio
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

unsigned long time;

void setup(){
  // Initalise serial terminal
  Serial.begin(57600);
  
  // Initalise radio device
  radio.begin(); 
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.setChannel(65);
  radio.startListening();
}

void loop(){
  int i;
  // Halt the program until an incoming message becomes available over radio.
  while(!radio.available()){}
  // Reads incoming message into the receiving buffer.
  while(!radio.read(text,32)){}
  // Prints contents of the receive buffer to the serial terminal.
  for(i=0;i<strlen(text);i++){
    Serial.print(text[i]);
  }
}
