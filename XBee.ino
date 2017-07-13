SoftwareSerial xBeeSerial = SoftwareSerial(xBeeRx, xBeeTx);
XBee xBee = XBee(&xBeeSerial, ID);

void xBeeSetup() {
  xBee.begin(9600);
  String header = "GPS Date,GPS Time,Type,Message";
  logRadio(header);
}

void sendXBee(String message) {
  digitalWrite(radioLED, HIGH);
  xBee.send(message);
  digitalWrite(radioLED, LOW);
  String data = getGPSdatetime() + ",TX," + message;
  logRadio(data);
}

void beacon(String data) {
  digitalWrite(radioLED, HIGH);
  xBee.send(data);
  digitalWrite(radioLED, LOW);
}

void xBeeCommand() {
  String command = xBee.receive();
  if (command.equals("")) return;
  else {
    digitalWrite(radioLED, HIGH);
    String data = getGPSdatetime() + ",RX," + command;
    logRadio(data);
    digitalWrite(radioLED, LOW);
  }
  if (command.equals("Something")) {
    //doSomething();
  }
  else if (command.equals("Other thing")) {
    //doOtherThing();
  }
   else {
     String message = "Error: " + command + " - command not recognized";
     sendXBee(message);
   }
}

