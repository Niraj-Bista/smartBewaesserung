/*
    @file main.cpp
    @brief SensorNode – einfacher Offline-Test (ohne Cloud).
    
    Ziel:
    - Bodenfeuchte über Analog-Ausgang (AO) einlesen
    - Rohwert im Serial Monitor anzeigen
    - optional: grobe Umrechnung in Prozent (mit Kalibrierwerten)
    
    Hardware:
    - LM393 Sensor-Modul: VCC -> 3.3V, GND -> GND, AO -> A0
    - Sonde am 2-poligen Anschluss des Moduls
 */

#include <Arduino.h>
#include "sensor_config.h"

// Hilfsfunktion: clamp (Wert begrenzen)
static int clampInt(int value, int minVal, int maxVal)
{
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

/*
    @brief Wandelt einen Rohwert in eine Prozentangabe um.
    
    Annahme (typisch):
    - RAW_DRY ist größer als RAW_WET.
    - Wenn  Sensor anders herum reagiert, tausche die Werte in sensor_config.h.
 */
static int rawToPercent(int raw)
{
    // Schutz: Division durch 0 vermeiden
    if (RAW_DRY == RAW_WET) return 0;

    // Bei vielen Sensoren gilt: trocken -> hoher Rohwert, nass -> niedriger Rohwert
    float pct = (float)(RAW_DRY - raw) * 100.0f / (float)(RAW_DRY - RAW_WET);
    int pctInt = (int)(pct + 0.5f); // runden
    return clampInt(pctInt, 0, 100);
}

unsigned long lastMeasureMs = 0;

void setup()
{
    Serial.begin(115200);
    while (!Serial) { /* warten bis Serial bereit */ }

    pinMode(PIN_SOIL_AO, INPUT);

    Serial.println("=== SensorNode Offline Test (AO -> A0) ===");
    Serial.println("Bewege den Sensor: Luft -> trockene Erde -> nasse Erde/Wasser.");
    Serial.println("Notiere RAW-Werte fuer RAW_WET und RAW_DRY in sensor_config.h");
    Serial.println();
}

void loop()
{
    const unsigned long now = millis();
    if (now - lastMeasureMs < MEASURE_INTERVAL_MS) {
        return;
    }
    lastMeasureMs = now;

    const int raw = analogRead(PIN_SOIL_AO);
    const int pct = rawToPercent(raw);

    Serial.print("RAW=");
    Serial.print(raw);
    Serial.print("  |  moisture=");
    Serial.print(pct);
    Serial.println("%");
}
