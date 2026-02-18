/**
 * thingProperties.h (SensorNode)
 * Kurzbeschreibung:
 * - Definiert die Cloud-Variablen für den Sensor-Node
 * - Sendet Messwerte (moisture_raw, moisture_pct) an das Dashboard
 * - Empfängt Einstellungen (threshold_pct) und das gemeinsame Signal (watering_command)
 * - Baut die WLAN/Cloud-Verbindung über WiFiConnectionHandler auf
 */
#include <secrets.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

// WLAN-Zugangsdaten aus secrets.h (nicht in Git speichern)
const char SSID[] = SECRET_SSID;
const char PASS[] = SECRET_OPTIONAL_PASS;

// Callback-Prototypen (werden bei Cloud-Änderungen aufgerufen)
void onWateringCommandChange();

// ===== Cloud-Variablen =====
// Messwerte (Device -> Cloud)
int moisture_pct;     // Bodenfeuchte in %
int moisture_raw;     // Rohwert vom Analogpin

// Einstellungen / Steuerung (Cloud <-> Device)
int  threshold_pct;   // Schwellwert in % (Dashboard einstellbar)
bool watering_command; // gemeinsames Signal: TRUE = Bewässerung anfordern

// Cloud-Properties registrieren
void initProperties() {

  // Sensorwerte nur lesen (Device schreibt, Cloud liest)
  ArduinoCloud.addProperty(moisture_pct, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(moisture_raw, READ, ON_CHANGE, NULL);


  // watering_command: kann vom Sensor (automatisch) oder Dashboard (manuell) gesetzt werden
  ArduinoCloud.addProperty(watering_command, READWRITE, ON_CHANGE, onWateringCommandChange);
}

// Verbindung für Nano 33 IoT: WLAN (NINA)
WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
