/**
 * @file main.cpp
 * @brief SensorNode – Bodenfeuchte messen und an Arduino IoT Cloud senden.
 *
 * Hardware:
 *  - Arduino Nano 33 IoT
 *  - Bodenfeuchtesensor (LM393 Modul)
 *  - AO  -> A0
 *  - VCC -> 3.3V
 *  - GND -> GND
 *
 * Funktion:
 *  - Liest den analogen Sensorwert
 *  - Wandelt ihn in Prozent um (Kalibrierung in sensor_config.h)
 *  - Überträgt Rohwert und Prozentwert an die Arduino IoT Cloud
 */


#include "thingProperties.h"
#include "sensor_config.h"

// Zeitsteuerung für Messintervalle / Cooldown
static unsigned long lastMeasureMs = 0;
static unsigned long lastTriggerMs = 0;

// Merker für Hysterese: waren wir schon "trocken"?
static bool wasDry = false;

/*
  Wandelt Sensor-Rohwert in Prozent um.
  Annahme: RAW_DRY ~ 0% (trocken), RAW_WET ~ 100% (nass)
 */
static int rawToPercent(int raw) {
  raw = constrain(raw, RAW_WET, RAW_DRY);
  int pct = map(raw, RAW_DRY, RAW_WET, 0, 100);
  return constrain(pct, 0, 100);
}

void setup() {
  Serial.begin(9600);
  delay(1500);

  pinMode(PIN_SOIL_AO, INPUT);

  // Cloud-Properties registrieren (generiert in thingProperties.h)
  initProperties();

  // Verbindung zur IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Sinnvoller Default, falls Dashboard/Cloud noch nichts gesetzt hat
  if (threshold_pct < 0 || threshold_pct > 100) threshold_pct = 35;

  Serial.println("=== SensorNode started ===");
}

void loop() {
  ArduinoCloud.update();

  // Messung nur im gewünschten Intervall
  if (millis() - lastMeasureMs < MEASURE_INTERVAL_MS) return;
  lastMeasureMs = millis();

  // 1) Messen
  moisture_raw = analogRead(PIN_SOIL_AO);
  moisture_pct = rawToPercent(moisture_raw);

  // 2) Debug-Ausgabe
  Serial.print("raw=");
  Serial.print(moisture_raw);
  Serial.print(" pct=");
  Serial.print(moisture_pct);
  Serial.print(" thr=");
  Serial.print(threshold_pct);
  Serial.print(" cmd=");
  Serial.println(watering_command ? "true" : "false");

  // 3) Trigger-Logik: trocken -> watering_command = true
  const bool below = (moisture_pct < threshold_pct);
  const bool aboveRelease = (moisture_pct >= (threshold_pct + HYSTERESIS_PCT));
  const bool cooldownOver = (millis() - lastTriggerMs >= COOLDOWN_MS);

  // Hysterese-Merker aktualisieren:
  // - Wenn wieder deutlich feuchter: "nicht mehr trocken"
  if (aboveRelease) wasDry = false;
  if (below) wasDry = true;
  Serial.println("wasDry");
  Serial.println(wasDry);
  Serial.println("cool down over");
  Serial.println(cooldownOver);
    // Nur triggern, wenn Cooldown vorbei und noch kein Command aktiv
  if (wasDry && cooldownOver) {
    Serial.println("water the plant");
    watering_command = true;      // bleibt TRUE bis Pump-Thing zurücksetzt
    lastTriggerMs = millis();
    Serial.println("-> Trigger watering_command = true (sensor)");
  }
  
    }
  




void onWateringCommandChange() {
  Serial.print("watering_command changed (cloud): ");
  Serial.println(watering_command ? "true" : "false");

  // Wenn die Pumpe es wieder auf false setzt, startet dadurch automatisch der Cooldown erneut.
  if (!watering_command) {
    lastTriggerMs = millis(); // optional: Cooldown ab "fertig" starten
  }
}


