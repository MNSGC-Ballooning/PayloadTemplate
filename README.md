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

The Payload Template sketch was built to be run on an Arduino Uno. However, it should be easy to
port to other boards, and in fact for large projects this is recommended - this sketch uses about
70% of both program storage and RAM on the Uno, and leaves only two digital pins unused.

As written, the sketch assumes the following digital pin connections. Entries in **bold** are
fixed by hardware or library specifications, while those in *italics* are strongly recommended,
but can be moved if needed.

0. *open*
1. *open*
2. GPS RX
3. GPS TX - SoftwareSerial connection
4. XBee RX
5. XBee TX - SoftwareSerial connection
6. open
7. open
8. Chip Select - Fixed for the shield this was developed on, but could be moved with a breakout.
9. data LED - flashes when data is written to the SD card.
10. *radio LED* - flashes when transmitting or receiving xBee communication.
11. **SD MOSI**
12. **SD MISO**
13. **SD SCK** - SPI limited to these pins, but more devices can be added, as it is a data bus.

*Note:* Pins 0 and 1 are *technically* open for use; however, they are shard by the USB port when
uploading code, and may cause problems when connected to sensors. Only use as a last resort.
Pin 10 can be moved, but must remain an output pin for SPI (including SD) connection to work.

## Using this template

Simply download the zip file and extract the contents to your project folder. Rename the sketch file
and folder to something appropriate for your project.  You will also need to assign a unique ID
to the xBee via the constant String variable in the [main sketch file.](PayloadTemplate.ino)
From there, make whatever edits and additions you need for your project.

Please don't clone this repository unless you wish to make changes to the template itself, as this
will lessen the chances of someone accidentally uploading their project code to the template repo.