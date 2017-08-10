/* Code to run a basic payload box featuring SD datalogging, GPS tracking, xBee communication, status LEDs, and additional sensors
 * Author: Ryan Bowers
 */

//Libraries needed
#include <SD.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Relay_XBee.h>

//Pin declarations
#define gpsRx 4
#define gpsTx 5
#define xBeeRx 6
#define xBeeTx 7
#define chipSelect 8
#define dataLED 9
#define radioLED 10

//ID for XBee communication. Choose something distinct relating to your payload, preferably short (2-4 characters, A-Z 0-9 only)
const String ID = "ID";

//each device has its own setup function
void setup() {
  SDsetup();
  sensorSetup();
  xBeeSetup();
}

//alternate between logging sensor data and checking for xBee commands
void loop() {
  updateSensors();
  xBeeCommand();
}

