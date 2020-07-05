#include <SoftwareSerial.h>

#include <Arduino.h>
#include "GravityTDS.h"

SoftwareSerial ArduinoUno(3,2);
#define TdsSensorPin A0
GravityTDS gravityTds;

float tdsValue = 0;

char rx_byte = 0;
String rx_str = "";

bool onoff = true;

void led() {
  if (onoff) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

void setup() {
  pinMode(TdsSensorPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  led();

  Serial.begin(9600);
  ArduinoUno.begin(4800);

  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(3.3);
  gravityTds.setAdcRange(1024);
  gravityTds.begin();
}

void loop() {
	if (ArduinoUno.available() > 0) {
	    rx_byte = ArduinoUno.read();
	    
	    if (rx_byte != '\n') {
	      rx_str += rx_byte;
	    }
	    else {
	    	if (rx_str == "tds") {
				gravityTds.update();
				tdsValue = gravityTds.getTdsValue();
				ArduinoUno.print("tds:");
				ArduinoUno.println(tdsValue,2);
	    	} else if (rx_str == "ledcek") {
				ArduinoUno.print("led:");
				if (onoff) {
					ArduinoUno.println("1");
			    } else {
					ArduinoUno.println("0");
			    }
	    	} else if (rx_str == "ledon") {
    			onoff = true;
    			led();
	    	} else if (rx_str == "ledoff") {
    			onoff = false;
    			led();
	    	} else if (rx_str.substring(0,7) == "tdscal:") {
      			String temp;
	    		temp = rx_str.substring(7);
	    		gravityTds.customCalibrate(temp.toFloat());
	    	} else {
      			ArduinoUno.println(rx_str);
	    	}

	      rx_str = "";
	    }
	}

	delay(30);
}