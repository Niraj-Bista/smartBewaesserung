#include <Arduino.h>

const int pumpPin = 5;   //  Pumpen-Pin eintragen

void setup() {
  pinMode(pumpPin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  unsigned long start = millis();
  while (!Serial && millis() - start<3000){} //max 3s warten

  Serial.println("firmware-sensor:boot ok");
}

void loop() {
  digitalWrite(pumpPin, HIGH);   // Pumpe AN
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("alive:LED ON");
  delay(500);
  

  digitalWrite(pumpPin, LOW);    // Pumpe AUS
  digitalWrite(LED_BUILTIN,LOW);
  Serial.println("notalive:LED OFF");
  delay(500);
}

