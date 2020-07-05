#include <SoftwareSerial.h>
SoftwareSerial ArduinoUno(3,2);

void setup(){
	Serial.begin(9600);
	ArduinoUno.begin(4800);

}

void loop(){
	int i = 10;
	ArduinoUno.print(i);
	ArduinoUno.println("\n");

	delay(30);
}