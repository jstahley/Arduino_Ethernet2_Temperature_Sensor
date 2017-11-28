/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 */

#include <SPI.h>
#include <Ethernet2.h>
#include "TemperatureSensor.h"

TemperatureSensor tempSensor = TemperatureSensor();

void setup() {
	// Open serial communications and wait for port to open:
	Serial.begin(9600);

	while (!Serial) {
		; // wait for serial port to connect. Needed for Leonardo only
	}
	Serial.print("Serial channel open \n");

	Serial.print("Calling Setup \n");
	tempSensor.Setup();
}

void loop() {
	
	tempSensor.PrintJson();
}

