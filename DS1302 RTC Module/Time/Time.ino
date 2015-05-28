/*
 * TimeRTC.pde
 * example code illustrating Time library with Real Time Clock.
 * 
 * Edited by Christopher Ho on 28/5/15
 * Changed the library to reflect our RTC Modules
 * Change Serial baud rate
 * Added the rtc pin declaration
 */

#include <Time.h>  
#include <Wire.h>  
#include <DS1302RTC.h>  // a basic DS1302 library that returns time as a time_t

// Set pins:  CE, IO,CLK
DS1302RTC RTC(27, 29, 31);

void setup()  {
  Serial.begin(115200);
  while (!Serial) ; // wait until Arduino Serial Monitor opens
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus()!= timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");      
}

void loop()
{
  if (timeStatus() == timeSet) {
    digitalClockDisplay();
  } else {
    Serial.println("The time has not been set.  Please run the Time");
    Serial.println("TimeRTCSet example, or DS1302RTC SetTime example.");
    Serial.println();
    delay(4000);
  }
  delay(1000);
}

void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

