//global variables for gps and sensor logging
SoftwareSerial gpsSerial = SoftwareSerial(gpsRx, gpsTx);
TinyGPS gps;
unsigned long timer = 0;
byte counter = 0;

//variables that gps data will be written to
float lat, lon, alt;
int sats, year;
byte month, day, hour, minute, second, hundreth;
unsigned long fixAge;

//setup function for gps and other sensors
void sensorSetup() {
  gpsSerial.begin(9600);
  String header = "GPS Time,Lat,Lon,Alt (m),# Sats,";  //this file goes at top of datalog. Add other sensor data to end
  logData(header);
  //other sensor setup goes here
}

//called repeatedly during loop()
void updateSensors() {
  //read gps data, check for new NMEA strings
  bool newData = false;
  while(gpsSerial.available() > 0) {
    if(gps.encode(gpsSerial.read()))
      newData = true;
  }
  //if new string is received, update gps variables
  if (newData) {
    gps.f_get_position(&lat, &lon, &fixAge);
    alt = gps.f_altitude();
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundreth, &fixAge);
    sats = gps.satellites();
  }
  //other repeated sensor processing goes here
  
  //once per second, log gps and sensor data
  if (millis() - timer > 1000) {
    timer = millis();
    counter++;

    //build data String via concatination (Note that all code before next semicolon is treated as one line)
    String data = String(hour) + ":" + String(minute) + ":" + String(second) + ","
                + String(lat, 4) + "," + String(lon, 4) + "," + String(alt, 1) + "," + String(sats) + ","
    //add extra sensor data as needed here
    
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
  return String(month) + "/" + String(day) + "/" + String(year) + "," + String(hour) + ":" + String(minute) + ":" + String(second);
}

