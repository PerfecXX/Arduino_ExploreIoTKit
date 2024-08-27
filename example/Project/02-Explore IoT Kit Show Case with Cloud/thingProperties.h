#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char SSID[] = "";
const char PASS[] = "";

float temperature;
float humidity;
bool led_state;
String message;
CloudSchedule scheduler;

void onTemperatureChange();
void onHumidityChange();
void onLedStateChange();
void onMessageChange();
void onSchedulerChange();

void initProperties() {
  ArduinoCloud.addProperty(message, READWRITE, ON_CHANGE, onMessageChange);
  ArduinoCloud.addProperty(humidity, READWRITE, ON_CHANGE, onHumidityChange);
  ArduinoCloud.addProperty(temperature, READWRITE, ON_CHANGE, onTemperatureChange);
  ArduinoCloud.addProperty(led_state, READWRITE, ON_CHANGE, onLedStateChange);
  ArduinoCloud.addProperty(scheduler, READWRITE, ON_CHANGE, onSchedulerChange);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
