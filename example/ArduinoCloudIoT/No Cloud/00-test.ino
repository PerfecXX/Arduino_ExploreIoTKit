#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <Arduino_MKRIoTCarrier.h>

const char SSID[] = "PX_SYSTEM_2.4G";  // Network SSID (name)
const char PASS[] = "PX123456789";     // Network password (use for WPA, or use as key for WEP)

void onMessageChange();
void onHumidityChange();
void onTemperatureChange();
void onLedStateChange();

String message;
float humidity;
float temperature;
bool led_state;

MKRIoTCarrier carrier;

uint32_t red = carrier.leds.Color(255, 0, 0);
uint32_t green = carrier.leds.Color(0, 255, 0);
uint32_t blue = carrier.leds.Color(0, 0, 255);
uint32_t yellow = carrier.leds.Color(255, 255, 0);
uint32_t cyan = carrier.leds.Color(0, 255, 255);
uint32_t off = carrier.leds.Color(0, 0, 0);

void setup() {
  carrier.begin();
  Serial.begin(9600);
  delay(1500);

  ArduinoCloud.addProperty(message, READWRITE, ON_CHANGE, onMessageChange);
  ArduinoCloud.addProperty(humidity, READWRITE, ON_CHANGE, onHumidityChange);
  ArduinoCloud.addProperty(temperature, READWRITE, ON_CHANGE, onTemperatureChange);
  ArduinoCloud.addProperty(led_state, READWRITE, ON_CHANGE, onLedStateChange);
  WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here
  temperature = carrier.Env.readTemperature();
  humidity = carrier.Env.readHumidity();
}

void onLedStateChange() {
  // Add your code here to act upon LedState change
  if (led_state == true) {
    Serial.println("LED ON!");
    carrier.leds.setPixelColor(0, red);     // Set LED 0 to red
    carrier.leds.setPixelColor(1, green);   // Set LED 1 to green
    carrier.leds.setPixelColor(2, blue);    // Set LED 2 to blue
    carrier.leds.setPixelColor(3, yellow);  // Set LED 3 to yellow
    carrier.leds.setPixelColor(4, cyan);    // Set LED 4 to cyan
    carrier.leds.show();
  } else {
    Serial.println("LED OFF!");
    carrier.leds.setPixelColor(0, off);
    carrier.leds.show();
  }
}
void onMessageChange() {
  // Add your code here to act upon Message change
  Serial.print("Message from Arduino Cloud");
  Serial.println(message);

  if (message == "buzzer on") {
    carrier.Buzzer.beep(800, 300);
  } else if (message == "relay1 on") {
    carrier.Relay1.open();
  } else if (message == "relay1 off") {
    carrier.Relay1.close();
  } else if (message == "relay1 off") {
    carrier.Relay1.close();
  } else if (message == "relay2 on") {
    carrier.Relay2.open();
  } else if (message == "relay2 off") {
    carrier.Relay2.close();
  }
  else if (message == "relay state"){
    message = "Relay1: " + String(carrier.Relay1.getStatus()) + ", Relay2: " + String(carrier.Relay2.getStatus());
  }
}
void onTemperatureChange() {}
void onHumidityChange() {}
