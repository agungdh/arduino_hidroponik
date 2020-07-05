#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server;

// const char* ssid = "dhdjdisjwhebe";
const char* ssid = ".,., ,, . ,, . . .,.,. ,.,., ,.";
const char* password = "12344334";

const char* ssidAP = "WiFi Arduino";
const char* passwordAP = "11223344";

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

	WiFi.softAP(ssidAP, passwordAP); 

  	WiFi.begin(ssid, password);

  	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.println("Still Connecting...");
	}

	Serial.println("WiFi Connected");
	Serial.println(WiFi.localIP());

	server.on("/on", []() {
		NodeMCU.println("ledon\n");

		Serial.print(NodeMCU.readString());
		if(NodeMCU.read()== '\n'){
			Serial.print("\n");
		}

		server.send(200, "text/html", "");
	});

	server.on("/off", []() {
		NodeMCU.println("ledoff\n");
		
		Serial.print(NodeMCU.readString());
		if(NodeMCU.read()== '\n'){
			Serial.print("\n");
		}

		server.send(200, "text/html", "");
	});

	server.begin();
}

void loop() {
  	server.handleClient();
}