/*
nRF24 Chatroom

Last modified: 2015 02 23

A simple multiway open chatroom.

For use with Nordic Semiconducor nRF24L01 2.4GHz which communicates with the Arduino over SPI.
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

// Setup radio
RF24 radio(9,10);
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };

unsigned long time;
char text[32];  //Doubles as the transmit and receive buffer

void setup(){
  // Initalise serial terminal
  Serial.begin(57600);
  
  // Initalise radio device
  radio.begin();
  radio.setRetries(15,15);
  radio.openWritingPipe(pipes[1]);
  radio.openReadingPipe(1,pipes[0]);
  radio.setChannel(65);
  radio.startListening();
}

int i;

void loop(){
  // Check to see if there are incoming messages
  if(radio.available()){          
    while(!radio.read(text,32)){} // Read it into the receiving buffer
    for(i=0;i<strlen(text);i++){  // and print it out to the serial monitor
      Serial.print(text[i]);
    }
  }
  // Outer while loop. Cycles infinitely until the input buffer is empty
  while(Serial.available()){
    // Stop listening mode in order to prepare to transmit messages.
    // Must be done prior to sending messages over radio.
    radio.stopListening();            
    i = 0;
    // Read in until the input buffer is empty or a a maximum of 30 characters is read into the 
    // transmit buffer. The transmit buffer has space for 32 characters, but the last two slots are
    // reserved for the newline and null character.
    while(Serial.available()&&i<30){
      text[i] = Serial.read();
      i++;
      delay(1);
    }
    if(Serial.available()){
      // After reading in up to 30 characters into the transmit buffer and there are still 
      // characters left in the input buffer, add a null terminator only to the transmit buffer.
      // The outer while loop will cycle back around and keep cycling until the input buffer is 
      // empty.
      text[i]='\0';
    } else {
      // If the input buffer is empty, append newline and terminate with null character.
      text[i] = '\n';
      text[i+1] = '\0';
    }
    // Echo your message back to the serial terminal.
    for(i=0;i<strlen(text);i++){
      Serial.print(text[i]);
    }
    // Send the transmit buffer over radio.
    radio.write(text,sizeof(text));
    // Resume listening mode for incoming messages.
    radio.startListening();
    delay(20);
  }
}
