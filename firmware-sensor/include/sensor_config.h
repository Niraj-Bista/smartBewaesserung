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
constexpr unsigned long MEASURE_INTERVAL_MS = 1000; // 1 Messung pro Sekunde

// ----- Kalibrierung (Platzhalter) ---
// Diese Werte trägst du später nach deinen Tests ein.
// Typisch: RAW_WET < RAW_DRY (aber das kann je nach Modul variieren!)
constexpr int RAW_WET = 300;   // Beispielwert: Sensor in Wasser / sehr nasse Erde
constexpr int RAW_DRY = 800;   // Beispielwert: Sensor in Luft / trockene Erde
