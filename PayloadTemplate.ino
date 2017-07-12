/* Code to run a basic payload box featuring SD datalogging, GPS tracking, xBee communication, status LEDs, and additional sensors
 * Author: Ryan Bowers
 */

#include <SD.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Relay_XBee.h>

#define dataLED 0
#define xBeeLED 1
#define gpsRx 2
#define gpsTx 3
#define xBeeRx 4
#define xBeeTx 5
#define chipSelect 8

void setup() {
  SDsetup();
  sensorSetup();
}

void loop() {
  updateSensors();
}

