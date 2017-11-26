#include <SPI.h>
#include <Ethernet2.h>
#define aref_voltage 3.3

class TemperatureSensor
{
	public:
		TemperatureSensor();
		void PrintHtml();
		void PrintJson();
		void Setup();

	private:
		int _analogReading;
		int _inputPin;
		EthernetServer _server = EthernetServer(80);
};