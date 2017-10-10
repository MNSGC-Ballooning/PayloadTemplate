//global variables for SD functions
File datalog, radiolog;
char datalogName[] = "Sensor00.csv";
char radiologName[] = "Radio00.csv";
bool datalogOpen = false, radiologOpen = false;

//standard SD initialization procedure
void SDsetup() {
  pinMode(dataLED_pin, OUTPUT);
  pinMode(chipSelect_pin, OUTPUT);
  if (!SD.begin(chipSelect_pin)) {  //Display an error if SD communication fails
    while(true) { //Note that this error loop is never broken - check for slow blinking LEDs before flying
      digitalWrite(dataLED_pin, HIGH);
      digitalWrite(radioLED_pin, HIGH);
      delay(500);
      digitalWrite(dataLED_pin, LOW);
      digitalWrite(radioLED_pin, LOW);
      delay(500);
    }
  }
  else {  //file creation process
    for (byte i = 0; i < 100; i++) {
      datalogName[6] = '0' + i/10;
      datalogName[7] = '0' + i%10;
      radiologName[5] = '0' + i/10;
      radiologName[6] = '0' + i%10;
      if (!SD.exists(datalogName) && !SD.exists(radiologName)) {  //make sure both file names are available before opening them
        openDatalog();
        openRadiolog();
        break;
      }
    }
  }
}

//functions to change file state (open/closed) and handle the appropriate status LED
void openDatalog() {
  if (!datalogOpen) {
    datalog = SD.open(datalogName, FILE_WRITE);
    datalogOpen = true;
    if (!radiologOpen)
      digitalWrite(dataLED_pin, HIGH);
  }
}

void openRadiolog() {
  if (!radiologOpen) {
    radiolog = SD.open(radiologName, FILE_WRITE);
    radiologOpen = true;
    if (!datalogOpen)
      digitalWrite(dataLED_pin, HIGH);
  }
}

void closeDatalog() {
  if (datalogOpen) {
    datalog.close();
    datalogOpen = false;
    if(!radiologOpen)
      digitalWrite(dataLED_pin, LOW);
  }
}

void closeRadiolog() {
  if (radiologOpen) {
    radiolog.close();
    radiologOpen = false;
    if(!datalogOpen)
      digitalWrite(dataLED_pin, LOW);
  }
}

//functions that handle both opening and closing of files when logging data to ensure it is saved properly
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

