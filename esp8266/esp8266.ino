#include <Arduino.h>
// #include <dummy.h>

bool onoff = true;

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

  Serial.begin(115200);
}

void loop() {
	Serial.println("ledon");
	delay(1000);
	Serial.println("ledoff");
	delay(1000);
}