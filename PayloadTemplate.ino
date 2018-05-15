/* Code to run a basic payload box featuring SD datalogging, GPS tracking, xBee communication, status LEDs, and additional sensors
 * Author: Ryan Bowers
 */

//Libraries needed
#include <SD.h>
#include <FlightGPS.h>  //Adafruit module
//#include <UbloxGPS.h> //Ublox module
#include <Relay_XBee.h>

//Pin declarations
#define gps_Serial Serial2
#define xBee_Serial Serial1
#define dataLED_pin 6
#define radioLED_pin 7
#define chipSelect_pin 53
//-----Add/change as needed-----


//ID for XBee communication. Choose something distinct relating to your payload, preferably short (2-4 characters, A-Z 0-9 only)
//----Make sure this gets changed from default-----
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

