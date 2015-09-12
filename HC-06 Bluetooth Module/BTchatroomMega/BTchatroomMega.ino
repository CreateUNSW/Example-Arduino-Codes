/*
Bluetooth Chatroom
CREATE UNSW

Written by: Nathan Adler
Updated by : Austin Kong
Last modified: 2015 09 12

For use with HC-06 Bluetooth Serial modules.
HC-06 can only act as a slave bluetooth device.

Uses extra hardware serial ports found an Arduino Mega

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

// Initialize the variables where we will store our data
char rx; // For messages received from bluetooth
char tx; // For messages to be sent to bluetooth

int sendFirst = 1;
int recvFirst = 1;

void setup(){
  // Begin serial terminal and bluetooth communication
  Serial3.begin(9600); //Remote device
  Serial.begin(9600);  //Your computer
  Serial.println("Welcome!");
}

void loop(){
  while(Serial3.available()){ // While bluetooth is sending a
                               // message to Arduino
    if (recvFirst)  {
      Serial.print("Recv: ");
      recvFirst = 0;
    }
    rx = Serial3.read();      // Read the data from bluetooth
    Serial.print(rx);          // Print it to our serial monitor
    delay(1);
    if(!Serial3.available()){ // If message is finished
      Serial.println();        // Print a new line to screen
      recvFirst = 1;
    }
    
  } // Loop if bluetooth message still being received
  
  while(Serial.available()){ // While Arduino is sending a message
                             // to bluetooth
    if (sendFirst)  {
      Serial.print("Send: ");
      sendFirst = 0;
    }
    tx = Serial.read();      // Read the data from serial monitor
    Serial.print(tx);        // Print the data to the monitor
    Serial3.print(tx);      // Send the message to bluetooth
    delay(1);
    if(!Serial.available()){ // If message is finished
      Serial.println();      // Print a new line to screen
      sendFirst = 1;
    }
  } // Loop if serial monitor message still being received
  
  // Loop forever
  
}
