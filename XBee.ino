SoftwareSerial xBeeSerial = SoftwareSerial(xBeeRx, xBeeTx);
XBee xBee = XBee(&xBeeSerial, ID);

void xBeeSetup() {
  xBee.begin(9600);
  String header = "GPS Date,GPS Time,Type,Message";
  logRadio(header);
}

void sendXBee(String message) {
  xBee.send(message);
  String data = getGPSdatetime() + ",TX," + message;
  logRadio(data);
}

void xBeeCommand() {
  String command = xBee.receive();
  if (command.equals("")) return;
  else {
    String data = getGPSdatetime() + ",RX," + command;
    logRadio(data);
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

