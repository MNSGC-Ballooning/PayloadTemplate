SoftwareSerial gpsSerial = SoftwareSerial(gpsRx, gpsTx);
TinyGPS gps;
unsigned long timer = 0;
byte counter = 0;

float lat, lon, alt;
int sats, year;
byte month, day, hour, minute, second, hundreth;
unsigned long fixAge;

void sensorSetup() {
  gpsSerial.begin(9600);
  String header = "GPS Date,GPS Time,Lat,Lon,Alt (m),# Sats,";
  logData(header);
}

void updateSensors() {
  bool newData = false;
  while(gpsSerial.available() > 0) {
    if(gps.encode(gpsSerial.read()))
      newData = true;
  }
  if (newData) {
    gps.f_get_position(&lat, &lon, &fixAge);
    alt = gps.f_altitude();
    gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundreth, &fixAge);
    sats = gps.satellites();
  }
  if (millis() - timer > 1000) {
    timer = millis();
    counter++;
    String data = String(month) + "/" + String(day) + "/" + String(year) + ",";
    data += String(hour) + ":" + String(minute) + ":" + String(second) + ",";
    data += String(lat, 4) + "," + String(lon, 4) + "," + String(alt, 1) + "," + String(sats) + ",";
    logData(data);
    if (counter == 10) {
      xBee.send(data);
      counter = 0;
    }
  }
}

String getGPSdatetime() {
  return String(month) + "/" + String(day) + "/" + String(year) + "," + String(hour) + ":" + String(minute) + ":" + String(second);
}

