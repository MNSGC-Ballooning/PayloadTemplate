//global xBee variables
SoftwareSerial xBeeSerial = SoftwareSerial(xBeeRx, xBeeTx);
XBee xBee = XBee(&xBeeSerial, ID);

//setup function for xBee
void xBeeSetup() {
  xBee.begin(9600);
  String header = "GPS Date,GPS Time,Type,Message";
  logRadio(header);
}

//function that simply beacons data to ground without logging
void beacon(String data) {
  digitalWrite(radioLED, HIGH);
  xBee.send(data);
  digitalWrite(radioLED, LOW);
}

//function that sends an xBee message and records it in the radio log
void sendXBee(String message) {
  digitalWrite(radioLED, HIGH);
  xBee.send(message);
  digitalWrite(radioLED, LOW);
  String data = getGPSdatetime() + ",TX," + message;
  logRadio(data);
}

//function to check for incoming xBee commands, called repeatedly during loop()
void xBeeCommand() {
  String command = xBee.receive();
  if (command.equals("")) return; //don't do anything if no command was received
  else {  //otherwise, log, then process the command
    digitalWrite(radioLED, HIGH);
    String data = getGPSdatetime() + ",RX," + command;
    logRadio(data);
    digitalWrite(radioLED, LOW);
  }
  //all commands go in a series of if-else statements; if a command matches a certain string, do a certain thing
  //keep commands short when possible - ~2-4 characters A-Z 0-9 only. At a minimum include ability to request data.
  if (command.equals("Something")) {
    //doSomething();
  }
  else if (command.equals("Other thing")) {
    //doOtherThing();
  }
   else { //if received command doesn't match any expected strings, inform ground of error
     String message = "Error: " + command + " - command not recognized";
     sendXBee(message);
   }
}

