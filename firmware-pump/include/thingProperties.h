/*#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

#include <secrets.h>
void onThresholdPctChange();
void onWaterDurationSChange();


int threshold_pct;
int water_duration_s;

void initProperties(){
  ArduinoCloud.addProperty(threshold_pct, READWRITE, ON_CHANGE, onThresholdPctChange);
  ArduinoCloud.addProperty(water_duration_s, READWRITE, 10 * SECONDS, onWaterDurationSChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);*/