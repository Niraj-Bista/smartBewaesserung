/**
 * @file main.cpp
 * @brief PumpNode – Offline-Relais-Test (ohne Cloud).
 *
 * Ziel:
 * - Relais schaltet im Sekundentakt EIN/AUS
 * - Du hörst ein "Klick"
 * - Optional: LED am Relais zeigt Status
 */

#include <Arduino.h>
#include "pump_config.h"

static void setRelay(bool on)
{
    // Viele Relaismodule sind active-low: LOW = EIN, HIGH = AUS
    if (RELAY_ACTIVE_LOW) {
        digitalWrite(PIN_RELAY_IN, on ? LOW : HIGH);
    } else {
        digitalWrite(PIN_RELAY_IN, on ? HIGH : LOW);
    }
}

void setup()
{
    Serial.begin(115200);
    delay(500);

    pinMode(PIN_RELAY_IN, OUTPUT);

    // Sicher: Relais aus
    setRelay(false);

    Serial.println("=== PumpNode Offline Relay Test ===");
}

void loop()
{
    Serial.println("Relay ON");
    setRelay(true);
    delay(TEST_ON_MS);

    Serial.println("Relay OFF");
    setRelay(false);
    delay(TEST_OFF_MS);
}
