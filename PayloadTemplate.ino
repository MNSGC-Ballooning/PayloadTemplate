/* Code to run a basic payload box featuring SD datalogging, GPS tracking, xBee communication, status LEDs, and additional sensors
 * Author: Ryan Bowers
 */

#include <SD.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Relay_XBee.h>

#define dataLED 0
#define xBeeLED 1
#define chipSelect 8



void setup() {
  SDsetup();
}

void loop() {
  
}

