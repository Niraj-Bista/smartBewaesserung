#include <Arduino.h>

/*void setup (){
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  delay(250);
  Serial.println("firmware-sensor:boot ok");
  delay(5000);
}
*/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);

  unsigned long start = millis();
  while (!Serial && millis() - start < 3000) { }  // max 3s warten

  Serial.println("firmware-sensor:boot ok");
}

void loop(){
  digitalWrite(LED_BUILTIN,HIGH);
  Serial.println("alive:LED ON");
  delay(500);

  digitalWrite(LED_BUILTIN,LOW);
  Serial.println("notalive:LED OFF");
  delay(500);
}