/*
Bluetooth Chatroom
CREATE UNSW

Written by: Nathan Adler
Last modified: 2015 02 23

For use with HC-06 Bluetooth Serial modules.
HC-06 can only act as a slave bluetooth device.


A two way (between bluetooth device and Arduino 
serial port) chatroom.
Also doubles as a AT command programer.
AT command programming must be performed from 
the Arduino via the bluetooth module's Rx, Tx
pins before it has been paired and connected.

This program echoes back what you type into the 
serial monitor and also forwards it to the 
bluetooth module.
Messages from the bluetooth module are also 
printed to the serial monitor.

Brief overview of AT commands and its 
acknowledgement message:
AT commands must be sent with no line ending.
Command           | Response
AT                  OK
AT+NAMEdevicename   OKsetname
AT+PIN1234          OKsetPIN

*/

#include <SoftwareSerial.h>

//Configure software serial to have RX on 9 and TX on 10.
//This means that the bluetooth RX is connected to pin 10
//and the bluetooth TX is connected to pin 9 (reversed).
SoftwareSerial mySerial(9,10);

// Initialize the variables where we will store our data
char rx; // For messages received from bluetooth
char tx; // For messages to be sent to bluetooth

void setup(){
  // Begin serial terminal and bluetooth communication
  mySerial.begin(9600);
  Serial.begin(9600);
}

void loop(){
  while(mySerial.available()){ // While bluetooth is sending a
                               // message to Arduino
    rx = mySerial.read();      // Read the data from bluetooth
    Serial.print(rx);          // Print it to our serial monitor
    
    if(!mySerial.available()){ // If message is finished
      Serial.println();        // Print a new line to screen
    }
    
  } // Loop if bluetooth message still being received
  
  while(Serial.available()){ // While Arduino is sending a message
                             // to bluetooth
    tx = Serial.read();      // Read the data from serial monitor
    Serial.print(tx);        // Print the data to the monitor
    mySerial.print(tx);      // Send the message to bluetooth
    
    if(!Serial.available()){ // If message is finished
      Serial.println();      // Print a new line to screen
    }
  } // Loop if serial monitor message still being received
  
  // Loop forever
  
}
