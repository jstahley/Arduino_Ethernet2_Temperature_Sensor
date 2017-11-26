#include "TemperatureSensor.h"
#include <SPI.h>
#include <Ethernet2.h>


TemperatureSensor::TemperatureSensor()
{
	_inputPin = 1;
}

void TemperatureSensor::PrintHtml()
{

	EthernetClient client = _server.available();

	if (client) {
		Serial.println("new client");
		// an http request ends with a blank line
		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				Serial.write(c);
				// if you've gotten to the end of the line (received a newline
				// character) and the line is blank, the http request has ended,
				// so you can send a reply
				if (c == '\n' && currentLineIsBlank) {
					// send a standard http response header
					client.println("HTTP/1.1 200 OK");
					client.println("Content-Type: text/html");
					client.println("Connection: close");  // the connection will be closed after completion of the response
														  // client.println("Refresh: 5");  // refresh the page automatically every 5 sec
					client.println();
					client.println("<!DOCTYPE HTML>");
					client.println("<html>");
					// output the value of each analog input pin

					_analogReading = analogRead(_inputPin);

					client.println("Temp reading: ");
					client.println("<br />");
					client.println("raw analog reading");
					client.println(_analogReading);     // the raw analog reading
					client.println("<br />");

					// converting that reading to voltage, which is based off the reference voltage
					float voltage = _analogReading * aref_voltage;
					voltage /= 1024.0;

					// print out the voltage
					client.println(voltage); client.println(" volts");
					client.println("<br />");
					// now print out the temperature
					float temperatureC = (voltage - 0.5) * 100;  //converting from 10 mv per degree wit 500 mV offset
																 //to degrees ((volatge - 500mV) times 100)
					client.println(temperatureC); client.println(" degrees C");
					client.println("<br />");
					// now convert to Fahrenheight
					float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
					client.println(temperatureF); client.println(" degrees F");
					client.println("<br />");
					delay(1000);

					client.println("</html>");
					break;
				}
				if (c == '\n') {
					// you're starting a new line
					currentLineIsBlank = true;
				}
				else if (c != '\r') {
					// you've gotten a character on the current line
					currentLineIsBlank = false;
				}
			}
		}
		// give the web browser time to receive the data
		delay(1);
		// close the connection:
		client.stop();
		Serial.println("client disconnected");
	}
}

void TemperatureSensor::PrintJson()
{



}

void TemperatureSensor::Setup()
{
	// Enter a MAC address and IP address for your controller below.
	// The IP address will be dependent on your local network:
	byte mac[] = {
		0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
	};

	IPAddress ip(192, 168, 1, 177);

	// Initialize the Ethernet server library
	// with the IP address and port you want to use
	// (port 80 is default for HTTP):
	EthernetServer server(80);

	// start the Ethernet connection and the server:
	Ethernet.begin(mac, ip);
	server.begin();
	Serial.print("server is at ");
	Serial.println(Ethernet.localIP());

	// If you want to set the aref to something other than 5v
	analogReference(EXTERNAL);
}
