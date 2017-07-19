//global variables for gps and sensor logging
SoftwareSerial gpsSerial = SoftwareSerial(gpsRx, gpsTx);
TinyGPS gps;
unsigned long timer = 0;
byte counter = 0;
int cycle = 0;

//variables that gps data will be written to
float lat, lon, alt;
int sats, year;
byte month, day, hour, minute, second, hundreth;
unsigned long fixAge;

//setup function for gps and other sensors
void sensorSetup() {
  gpsSerial.begin(9600);
  //this line goes at top of datalog. Add other sensor data to end
  String header = "ID,Cycle,Hour,Min,Sec,Lat,Lon,Alt,Sats,Sensor1,Sensor2,Sensor3,Sensor4,Special1,Special2,Checksum";
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
    cycle++;
    String data = getSensorData();
    String sum = String(checksum(data));
    logData(data + "," + sum);
    
    //once per 10 logging cycles, send most recent data to ground
    if (counter == 10) {
      beacon(data);
      counter = 0;
    }
  }
}

byte checksum(String data) {
  byte sum = 0;
  for(int i=0; i < data.length(); i++) {
    sum += byte(data.charAt(i));
  }
  return checksum;
}

//function to quickly get most recent gps time in hour,min,sec format
String getGPStime() {
  return String(hour) + "," + String(minute) + "," + String(second);
}

//function to assemble sensor data for logging and transmit
String getSensorData() {
  String data = 
  data += String(hour) + "," + String(minute) + "," + String(second) + ",";
  data += String(lat, 4) + "," + String(lon, 4) + "," + String(alt, 1) + "," + String(sats) + ",";
  //add additional sensor data as needed
  return data;
}

