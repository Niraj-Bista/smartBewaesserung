
#include <secrets.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

void onWaterDurationSChange();
void onWateringCommandChange();

int water_duration_s;
bool pump_ready=false;
bool pump_state;
bool watering_command;

void initProperties(){

  ArduinoCloud.addProperty(water_duration_s, READWRITE, ON_CHANGE, onWaterDurationSChange);
  ArduinoCloud.addProperty(pump_ready, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(pump_state, READ, ON_CHANGE, NULL);
  ArduinoCloud.addProperty(watering_command, READWRITE, ON_CHANGE, onWateringCommandChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);