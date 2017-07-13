File datalog, radiolog;
char datalogName[] = "SENSOR00.csv";
char radiologName[] = "RADIO00.csv";
bool datalogOpen = false, radiologOpen = false;

void SDsetup() {
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    while(true) {
      digitalWrite(dataLED, HIGH);
      digitalWrite(radioLED, HIGH);
      delay(500);
      digitalWrite(dataLED, LOW);
      digitalWrite(radioLED, LOW);
      delay(500);
    }
  }
  else {
    for (byte i = 0; i < 100; i++) {
      datalogName[6] = '0' + i/10;
      datalogName[7] = '0' + i%10;
      radiologName[5] = '0' + i/10;
      radiologName[6] = '0' + i%10;
      if (!SD.exists(datalogName) && !SD.exists(radiologName)) {
        openDatalog();
        openRadiolog();
        break;
      }
    }
  }
}

void openDatalog() {
  if (!datalogOpen) {
    datalog = SD.open(datalogName, FILE_WRITE);
    datalogOpen = true;
    if (!radiologOpen)
      digitalWrite(dataLED, HIGH);
  }
}

void openRadiolog() {
  if (!radiologOpen) {
    radiolog = SD.open(radiologName, FILE_WRITE);
    radiologOpen = true;
    if (!datalogOpen)
      digitalWrite(dataLED, HIGH);
  }
}

void closeDatalog() {
  if (datalogOpen) {
    datalog.close();
    datalogOpen = false;
    if(!radiologOpen)
      digitalWrite(dataLED, LOW);
  }
}

void closeRadiolog() {
  if (radiologOpen) {
    radiolog.close();
    radiologOpen = false;
    if(!datalogOpen)
      digitalWrite(dataLED, LOW);
  }
}

void logData(String data) {
  openDatalog();
  datalog.println(data);
  closeDatalog();
}

void logRadio(String message) {
  openRadiolog();
  radiolog.println(message);
  closeRadiolog();
}

