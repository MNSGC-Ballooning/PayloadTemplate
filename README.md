# Payload Template

Most ballooning payloads require very similar basic functionalities to be implemented in order to
achieve their mission objectives, including logging data, communicating with the ground, and
tracking location with gps. Often, little variation exists in how these functionalities are
implemented in code, so this sketch aims to speed the inital development of payload code by
providing a framework for these functions. This allows users to skip to working on developing code
to drive the components unique to their particular project.

## Functionalities included in the Payload Template

As written, the Payload Template sketch will already perform the following without modification:

* Set up files for datalogging on an SD card, implemented using the built-in Arduino SD library.
* Run a GPS sensor, implemented using the [TinyGPS](https://github.com/mikalhart/TinyGPS) library.
* Log GPS sensor data to the SD card once per second.
* Communicate with a relay payload via xBee, implemented using the
	[Relay_XBee](https://github.com/MNSGC-Ballooning/Relay-XBee) library.
* Transmit GPS data to the relay once per 10 seconds.

In addition, the sketch is organized so that the following can be added relatively easily:

* Additional sensors for passive data recording.
* Commands to trigger payload actions from ground via xBee relay.

Implementing anything more complicated than this will likely still require significant effort on the
part of the developers.

## Wiring for the sketch

The Payload Template sketch was built to be run on an Arduino Mega. However, it should be easy to
port to other boards with comperable or larger available memory. Although it is possible to run
this sketch on an Uno, it already uses about 70% of both program storage and RAM and leaves only two
digital pins unused, allowing little room for additional features of specific projects.

As written, the sketch assumes the following digital pin connections. Entries in **bold** are
fixed by hardware or library specifications, while those in *italics* are strongly recommended,
but can be moved if needed. If a pin isn't listed, it's available without restriction.

### USB pins*

0. *reserved*
1. *reserved*

### LED Pins

6. data LED
7. radio LED

### Serial Pins**

16. *GPS TX*
17. *GPS RX*
18. *XBee TX*
19. *XBee RX*

### SD Pins

50. **SD MISO**
51. **SD MOSI**
52. **SD SCK** - SPI limited to these pins, but more devices can be added, as it is a data bus.
53. *SD Chip Select* - Chip Select can be moved, but pin 53 must be an output for SD library to work.

*Pins 0 and 1 are *technically* open for use; however, they are shared by the USB port when
uploading code, and may cause problems when connected to sensors. Since the Mega has over 50  other
digital pins, it's best to just avoid these unless required by a shield or library.  
**The Mega has 3 hardware serial lines that should be used first for any serial connection.
However, the order doesn't matter and if necessary the SoftwareSerial library can be used to move
these connections to other pins.


## Using this template

Simply download the zip file and extract the contents to your project folder. Rename **both** the
sketch file and folder to something appropriate for your project.  You will also need to assign a
unique ID to the xBee via the constant String variable in the [main sketch file.](PayloadTemplate.ino)
From there, make whatever edits and additions you need for your project.

Please don't clone this repository unless you wish to make changes to the template itself, as this
will lessen the chances of someone accidentally uploading their project code to the template repo.