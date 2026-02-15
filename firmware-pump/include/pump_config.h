#pragma once
/**
 * Pumpen-Hardware Einstellungen
 * - definiert Relais-Pin
 * - merkt sich ob gerade gegossen wird
 * - enthält Funktion zum Ein/Ausschalten der Pumpe
 */

#include <Arduino.h>

// Relais an Digital-Pin 2
constexpr uint8_t PIN_RELAY_IN = 2;

// true = LOW schaltet EIN (typisch bei Relaismodulen)
constexpr bool RELAY_ACTIVE_LOW = true;

// aktueller Pumpenzustand
bool isWatering = false;

// Zeitpunkt wann die Pumpe stoppen soll (millis)
unsigned long wateringEndMs = 0;


// Relais (und damit Pumpe) schalten
void setRelay(bool on) {
  if (RELAY_ACTIVE_LOW) {
    digitalWrite(PIN_RELAY_IN, on ? LOW : HIGH);
  } else {
    digitalWrite(PIN_RELAY_IN, on ? HIGH : LOW);
  }
}



