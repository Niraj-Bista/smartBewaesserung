#pragma once
/**
 * @file pump_config.h
 * @brief Hardware-Konfiguration PumpNode (offline & Cloud).
 */

#include <Arduino.h>

constexpr uint8_t PIN_RELAY_IN = 2;          // Relais IN an D2
constexpr bool RELAY_ACTIVE_LOW = true;      // viele Relais sind "LOW = an"
constexpr unsigned long TEST_ON_MS  = 1000;
constexpr unsigned long TEST_OFF_MS = 1000;
