#pragma once   //Diese Header-Datei darf pro Übersetzungseinheit nur einmal eingebunden werden.
/**
 * @file sensor_config.h
 * @brief Zentrale Konfiguration für den SensorNode (ohne Cloud).
 *
 * Hinweis:
 * - Nano 33 IoT nutzt 3.3V Logik. Sensor-Modul daher mit 3.3V betreiben.
 * - Wir lesen AO (Analog Output) am Pin A0 aus.
 */

#include <Arduino.h>

// ---- Hardware Pins -----
constexpr uint8_t PIN_SOIL_AO = A0;   // AO vom Sensor-Modul (LM393 Board) an A0

// ---- Messung -----
constexpr unsigned long MEASURE_INTERVAL_MS = 5000; // alle 5 sekunden

// ----- Kalibrierung (Platzhalter) ---
// Diese Werte trägst du später nach deinen Tests ein.
// Typisch: RAW_WET < RAW_DRY (aber das kann je nach Modul variieren!)
constexpr int RAW_WET = 330;   // nasse Erde/Wasser ~323–333
constexpr int RAW_DRY = 1023;   // Luft/trocken ~1020–1023
