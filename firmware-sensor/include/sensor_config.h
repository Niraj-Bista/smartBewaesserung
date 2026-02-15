#pragma once
/**
 * SensorNode Hardware- und Mess-Konfiguration
 * - definiert Sensor-Pin
 * - Kalibrierwerte für trocken/nass
 * - Schutz gegen zu häufiges Auslösen
 */

#include <Arduino.h>

/* Analoger Ausgang des Bodenfeuchtesensors */
constexpr uint8_t PIN_SOIL_AO = A0;


/* Wie oft messen (Millisekunden) */
constexpr unsigned long MEASURE_INTERVAL_MS = 1000;   // 1 Sekunde


/* Kalibrierung des Sensors
   RAW_DRY = Messwert in trockener Luft
   RAW_WET = Messwert im Wasser
   → daraus wird Prozent berechnet
*/
constexpr int RAW_WET = 330;      // sehr nass
constexpr int RAW_DRY = 1023;     // sehr trocken


/* Stabilität / Schutzlogik */

// verhindert schnelles Ein/Aus nahe der Grenze
constexpr int HYSTERESIS_PCT = 5;

// Wartezeit nach Bewässerung (damit Erde Wasser aufnehmen kann)
constexpr unsigned long COOLDOWN_MS = 120000UL;   // 2 Minuten