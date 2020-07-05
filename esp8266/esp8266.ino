#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

bool onoff = true;

SoftwareSerial NodeMCU(D2,D3);

void led() {
	if (!onoff) {
		digitalWrite(LED_BUILTIN, HIGH);
	} else {
		digitalWrite(LED_BUILTIN, LOW);
	}
}

void setup() {
	pinMode(LED_BUILTIN, OUTPUT);

	led();

	Serial.begin(9600);
	NodeMCU.begin(4800);

	pinMode(D2,INPUT);
	pinMode(D3,OUTPUT);
}

void loop() {
	while(NodeMCU.available()>0){
		NodeMCU.println("ledon\n");
		delay(1000);
		NodeMCU.println("ledoff\n");
		delay(1000);
	}
	
	delay(30);
}