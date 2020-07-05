#include <Arduino.h>
#include "GravityTDS.h"

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

  Serial.begin(115200);

  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);
  gravityTds.setAdcRange(1024);
  gravityTds.begin();

  Serial.println("Macchinoo Sta'toooo");
}

void loop() {
	if (Serial.available() > 0) {
	    rx_byte = Serial.read();
	    
	    if (rx_byte != '\n') {
	      rx_str += rx_byte;
	    }
	    else {
	    	if (rx_str == "tds") {
				gravityTds.update();
				tdsValue = gravityTds.getTdsValue();
				Serial.print("tds:");
				Serial.println(tdsValue,2);
	    	} else if (rx_str == "ledcek") {
				Serial.print("led:");
				if (onoff) {
					Serial.println("1");
			    } else {
					Serial.println("0");
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
      			Serial.println(rx_str);
	    	}

	      rx_str = "";
	    }
  }
}