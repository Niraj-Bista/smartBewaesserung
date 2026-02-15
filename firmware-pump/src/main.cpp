/**
 * PumpNode – Cloud-gesteuerte Bewässerung
 *
 * Relais Steuerseite:
 *  IN  -> D2
 *  GND -> GND
 *  VCC -> 3,3V 
 *
 * Relais Klemmen:
 *  COM + NO schalten die Plusleitung der Pumpe
 *
 * Cloud-Variablen:
 *  watering_command , water_duration_s , pump_state , pump_ready
 */

#include "Arduino.h"
#include "thingProperties.h"
#include "pump_config.h"

// Optional: Dauer begrenzen (Sicherheitslimit)
static const int MIN_DURATION_S = 1;
static const int MAX_DURATION_S = 20;

void setup() {
  // Serial (für Debug)
  Serial.begin(9600);
  delay(1500);

  // Relais Hardware vorbereiten
  pinMode(PIN_RELAY_IN, OUTPUT);
  setRelay(false);

  // IoT Cloud Properties initialisieren (generiert in thingProperties.h)
  initProperties();

  // Verbindung zur Arduino IoT Cloud starten
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  // Debug-Ausgaben (0..4)
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  // Dashboard-Status: Gerät läuft
  pump_ready = true;       // LED "bereit" an
  pump_state = false;      // Anzeige

  Serial.println("=== PumpNode started ===");
}

void loop() {
  // Cloud synchronisieren (muss regelmäßig laufen)
  ArduinoCloud.update();

  // Wenn Pumpe läuft: prüfen, ob Zeit vorbei ist
  if (isWatering && millis() >= wateringEndMs) {
    setRelay(false);
    isWatering = false;
    pump_state = false;

    // ACK: Command zurücksetzen, damit Sensor/Dashboard weiß "fertig"
    watering_command = false;

    Serial.println("Watering finished.");
  }
}

/**
 * @brief Wird aufgerufen, wenn watering_command in der Cloud geändert wurde.
 * Voraussetzung: watering_command ist READ_WRITE im Thing.
 */
void onWateringCommandChange() {
  Serial.print("watering_command changed: ");
  Serial.println(watering_command ? "true" : "false");

  // Nur starten, wenn Command TRUE und Pumpe nicht schon läuft
  if (watering_command && !isWatering) {

    int duration = water_duration_s;

    // Sicherheitsgrenzen
    if (duration < MIN_DURATION_S) duration = MIN_DURATION_S;
    if (duration > MAX_DURATION_S) duration = MAX_DURATION_S;

    // Pumpe starten
    setRelay(true);
    isWatering = true;

    // Status fürs Dashboard
    pump_ready = true;   // LED "läuft" an
    pump_state = true;

    // Endezeit berechnen
    wateringEndMs = millis() + (unsigned long)duration * 1000UL;

    Serial.print("Start watering for ");
    Serial.print(duration);
    Serial.println(" s");
  }
}

/**
 * @brief Wird aufgerufen, wenn water_duration_s in der Cloud geändert wurde.
 * Hier nur validieren/begrenzen.
 */
void onWaterDurationSChange() {
  if (water_duration_s < MIN_DURATION_S) water_duration_s = MIN_DURATION_S;
  if (water_duration_s > MAX_DURATION_S) water_duration_s = MAX_DURATION_S;

  Serial.print("New duration set: ");
  Serial.println(water_duration_s);
}


