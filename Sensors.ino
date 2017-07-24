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
  String header = "ID,Cycle,Hour,Min,Sec,Lat,Lon,Alt,Sats,Sensor1,Sensor2,Sensor3,Sensor4,Checksum,Special1,Special2";
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
    char dataString[arraySize] = {0};
    getSensorData(dataString);
    logData(dataString);
    
    //once per 60 logging cycles, send most recent data to ground
    if (counter == 60) {
      beacon(dataString);
      counter = 0;
    }
  }
}

//function to quickly get most recent gps time in hour,min,sec format
String getGPStime() {
  return String(hour) + "," + String(minute) + "," + String(second);
}

//function to assemble sensor data for logging and transmit
char* getSensorData(char dataString[]) {
  byte pos = 0;
  addData(ID, dataString, &pos);
  addData(String(cycle), dataString, &pos);
  addData(String(hour), dataString, &pos);
  addData(String(minute), dataString, &pos);
  addData(String(second), dataString, &pos);
  addData(String(lat, 4), dataString, &pos);
  addData(String(lon, 4), dataString, &pos);
  addData(String(alt, 1), dataString, &pos);
  addData(String(sats), dataString, &pos);
  //add additional sensor data as needed
  //checksum
  byte sum = 0;
  for(byte i = 0; i < pos; i++) {
    sum += byte(dataString[i]);
  }
  addData(String(sum), dataString, &pos);
  return dataString;
}

void addData(String data, char dataString[], byte* pos) {
  char arr[data.length() + 1];
  data.toCharArray(arr, sizeof(arr));
  arr[data.length()] = ',';
  for (byte i = 0; i < sizeof(arr); i++) {
    dataString[(*pos)] = arr[i];
    (*pos)++;
  }
}
