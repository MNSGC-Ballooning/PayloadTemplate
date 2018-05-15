//global variables for gps and sensor logging
FlightGPS gps = FlightGPS(&gps_Serial); //Adafruit module
//UbloxGPS gps = UbloxGPS(&gps_Serial); //Ublox module
unsigned long timer = 0;
byte counter = 0;

//setup function for gps and other sensors
void sensorSetup() {
  gps.initialize();
  String header = "GPS Time,Lat,Lon,Alt (m),# Sats,";  //this file goes at top of datalog. Add other sensor data to end
  logData(header);
  //other sensor setup goes here
}

//called repeatedly during loop()
void updateSensors() {
  //check for new gps data
  gps.update();
  //---------------------------------------------
  //other repeated sensor processing goes here

  //---------------------------------------------
  
  //once per second, log gps and sensor data
  if (millis() - timer > 1000) {
    timer = millis();
    counter++;

    //build data String via concatination (Note that all code before next semicolon is treated as one line)
    String data = String(gps.getHour()) + ":" + String(gps.getMinute()) + ":" + String(gps.getSecond()) + ","
                + String(gps.getLat(), 4) + "," + String(gps.getLon(), 4) + "," + String(gps.getAlt(), 1) + ","
                + String(gps.getSats()) + ","
                //---------------------------------------------
                //add extra sensor data as needed here

                //---------------------------------------------
    ; //end of data String
    
    logData(data);
    
    //once per 10 logging cycles, send most recent data to ground
    if (counter == 10) {
      beacon(data);
      counter = 0;
    }
  }
}

//function to quickly get most recent gps date and time as a single string
String getGPStime() {
  return String(gps.getMonth()) + "/" + String(gps.getDay()) + "/" + String(gps.getYear()) + ","
          + String(gps.getHour()) + ":" + String(gps.getMinute()) + ":" + String(gps.getSecond());
}

